/****************************************************************************
 * Copyright (c) 2012, the Konoha project authors. All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *	this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in the
 *	documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ***************************************************************************/

#ifdef USE_DUMP_VISITOR
#include <stdio.h>

#define DUMPER(BUILDER)  ((struct DumpVisitorLocal *)(BUILDER)->local_fields)

#ifdef __cplusplus
extern "C" {
#endif

static void emit_string(const char *str, const char *prefix, const char *suffix, int indent)
{
	int i;
	for (i = 0; i < indent; i++) {
		putchar(' ');
	}
	printf("%s%s%s\n", prefix, str, suffix);
}

static void DumpVisitor_visitErrStmt(KonohaContext *kctx, IRBuilder *self, kStmt *stmt)
{
	emit_string(S_text(kStmt_GetObjectNULL(kctx, stmt, KW_ERR)), "", "", DUMPER(self)->indent);
}

static void DumpVisitor_visitExprStmt(KonohaContext *kctx, IRBuilder *self, kStmt *stmt)
{
	handleExpr(kctx, self, Stmt_getFirstExpr(kctx, stmt));
}

static void DumpVisitor_visitBlockStmt(KonohaContext *kctx, IRBuilder *self, kStmt *stmt)
{
	visitBlock(kctx, self, Stmt_getFirstBlock(kctx, stmt));
}

static void DumpVisitor_visitReturnStmt(KonohaContext *kctx, IRBuilder *self, kStmt *stmt)
{
	emit_string("Return", "", "", DUMPER(self)->indent);
	kExpr* expr = Stmt_getFirstExpr(kctx, stmt);
	if(expr != NULL && IS_Expr(expr)) {
		handleExpr(kctx, self, expr);
	}
}

static void DumpVisitor_visitIfStmt(KonohaContext *kctx, IRBuilder *self, kStmt *stmt)
{
	DUMPER(self)->indent++;
	emit_string("If", "", "", DUMPER(self)->indent - 1);
	handleExpr(kctx, self, Stmt_getFirstExpr(kctx, stmt));
	emit_string("Then", "", "", DUMPER(self)->indent - 1);
	visitBlock(kctx, self, Stmt_getFirstBlock(kctx, stmt));
	emit_string("Else", "", "", DUMPER(self)->indent - 1);
	visitBlock(kctx, self, Stmt_getElseBlock(kctx, stmt));
	DUMPER(self)->indent--;
}

static void DumpVisitor_visitLoopStmt(KonohaContext *kctx, IRBuilder *self, kStmt *stmt)
{
	DUMPER(self)->indent++;
	emit_string("Loop", "", "", DUMPER(self)->indent - 1);
	handleExpr(kctx, self, Stmt_getFirstExpr(kctx, stmt));
	emit_string("Body", "", "", DUMPER(self)->indent - 1);
	visitBlock(kctx, self, Stmt_getFirstBlock(kctx, stmt));
	DUMPER(self)->indent--;
}

static void DumpVisitor_visitJumpStmt(KonohaContext *kctx, IRBuilder *self, kStmt *stmt)
{
	emit_string("Jump", "", "", DUMPER(self)->indent);
}

static void DumpVisitor_visitTryStmt(KonohaContext *kctx, IRBuilder *self, kStmt *stmt)
{
	DUMPER(self)->indent++;
	emit_string("Try", "", "", DUMPER(self)->indent - 1);
	visitBlock(kctx, self, Stmt_getFirstBlock(kctx, stmt));
	kBlock *catchBlock   = SUGAR kStmt_GetBlock(kctx, stmt, NULL, SYM_("catch"),   K_NULLBLOCK);
	kBlock *finallyBlock = SUGAR kStmt_GetBlock(kctx, stmt, NULL, SYM_("finally"), K_NULLBLOCK);
	if(catchBlock != K_NULLBLOCK){
		emit_string("Catch", "", "", DUMPER(self)->indent - 1);
		visitBlock(kctx, self, catchBlock);
	}
	if(finallyBlock != K_NULLBLOCK){
		emit_string("Finally", "", "", DUMPER(self)->indent - 1);
		visitBlock(kctx, self, finallyBlock);
	}
	DUMPER(self)->indent--;
}

static void DumpVisitor_visitUndefinedStmt(KonohaContext *kctx, IRBuilder *self, kStmt *stmt)
{
	emit_string("UNDEF", "", "", DUMPER(self)->indent);
}

static void DumpVisitor_visitConstExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	KGrowingBuffer wb;
	KLIB Kwb_Init(&(kctx->stack->cwb), &wb);
	KonohaStack sfp[1];
	kObject *obj = expr->objectConstValue;
	sfp[0].asObject = obj;
	O_ct(obj)->p(kctx, sfp, 0, &wb);
	char  *str = (char *) KLIB Kwb_top(kctx, &wb, 0);
	char buf[128];
	snprintf(buf, 128, "CONST:%s:'%s'", CT_t(O_ct(obj)), str);
	emit_string(buf, "", "", DUMPER(self)->indent);
	KLIB Kwb_Free(&wb);
}

static void DumpVisitor_visitNConstExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	KGrowingBuffer wb;
	KLIB Kwb_Init(&(kctx->stack->cwb), &wb);
	KonohaStack sfp[1];
	unsigned long unboxVal = expr->unboxConstValue;
	KonohaClass *ct = CT_(expr->ty);
	sfp[0].unboxValue = unboxVal;
	ct->p(kctx, sfp, 0, &wb);
	char  *str = (char *) KLIB Kwb_top(kctx, &wb, 0);
	char buf[128];
	snprintf(buf, 128, "NCONST:'%s'", str);
	emit_string(buf, "", "", DUMPER(self)->indent);
	KLIB Kwb_Free(&wb);
}

static void DumpVisitor_visitNewExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	emit_string("NEW", "", "", DUMPER(self)->indent);
}

static void DumpVisitor_visitNullExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	char buf[128];
	snprintf(buf, 128, "%s.NULL", CT_t(CT_(expr->ty)));
	emit_string(buf, "", "", DUMPER(self)->indent);
}

static void DumpVisitor_visitLocalExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	char buf[128];
	snprintf(buf, 128, "LOCAL(%d, %s)", (int)expr->index, CT_t(CT_(expr->ty)));
	emit_string(buf, "", "", DUMPER(self)->indent);

}

static void DumpVisitor_visitBlockExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	emit_string("BLOCK", "", "", DUMPER(self)->indent);
	visitBlock(kctx, self, expr->block);
}

static void DumpVisitor_visitFieldExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	emit_string("FIELD", "", "", DUMPER(self)->indent);
}

static void DumpVisitor_visitCallExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	KGrowingBuffer wb;
	KLIB Kwb_Init(&(kctx->stack->cwb), &wb);
	kMethod *mtd = CallExpr_getMethod(expr);
	KLIB Kwb_printf(kctx, &wb, "CALL: '%s%s'", MethodName_t(mtd->mn));
	DUMPER(self)->indent++;
	emit_string(KLIB Kwb_top(kctx, &wb, 1), "(", "", DUMPER(self)->indent);
	DUMPER(self)->indent++;
	unsigned i;
	for (i = 1; i < kArray_size(expr->cons); ++i) {
		handleExpr(kctx, self, kExpr_at(expr, i));
	}
	DUMPER(self)->indent--;
	emit_string(")", "", "", DUMPER(self)->indent);
	DUMPER(self)->indent--;
	KLIB Kwb_Free(&wb);
}

static void DumpVisitor_visitAndExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	unsigned i;
	emit_string("AND", "", "", DUMPER(self)->indent);
	DUMPER(self)->indent++;
	for (i = 1; i < kArray_size(expr->cons); ++i) {
		handleExpr(kctx, self, kExpr_at(expr, i));
	}
	DUMPER(self)->indent--;
}

static void DumpVisitor_visitOrExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	unsigned i;
	emit_string("OR", "", "", DUMPER(self)->indent);
	DUMPER(self)->indent++;
	for (i = 1; i < kArray_size(expr->cons); ++i) {
		handleExpr(kctx, self, kExpr_at(expr, i));
	}
	DUMPER(self)->indent--;
}

static void DumpVisitor_visitLetExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	DUMPER(self)->indent++;
	emit_string("LET ", "", "", DUMPER(self)->indent);
	DUMPER(self)->indent++;
	handleExpr(kctx, self, kExpr_at(expr, 1));
	emit_string(":=", "", "", DUMPER(self)->indent);
	handleExpr(kctx, self, kExpr_at(expr, 2));
	DUMPER(self)->indent--;
	DUMPER(self)->indent--;
}

static void DumpVisitor_visitStackTopExpr(KonohaContext *kctx, IRBuilder *self, kExpr *expr)
{
	emit_string("STACKTOP", "", "", DUMPER(self)->indent);
}

static void DumpVisitor_Init(KonohaContext *kctx, struct IRBuilder *builder, kMethod *mtd)
{
	unsigned i;
	KGrowingBuffer wb;
	KLIB Kwb_Init(&(kctx->stack->cwb), &wb);
	kParam *pa = Method_param(mtd);
	KLIB Kwb_printf(kctx, &wb, "METHOD %s%s(", MethodName_t(mtd->mn));
	for (i = 0; i < pa->psize; i++) {
		if(i != 0) {
			KLIB Kwb_write(kctx, &wb, ", ", 2);
		}
		KLIB Kwb_printf(kctx, &wb, "%s %s", TY_t(pa->paramtypeItems[i].ty), SYM_t(pa->paramtypeItems[i].fn));
	}
	emit_string(KLIB Kwb_top(kctx, &wb, 1), "", ") {", 0);
	builder->local_fields = (void *) KMalloc_UNTRACE(sizeof(int));
	DUMPER(builder)->indent = 0;
}

void DumpVisitor_Free(KonohaContext *kctx, struct IRBuilder *builder, kMethod *mtd)
{
	emit_string("}", "", "", 0);
	KFree(builder->local_fields, sizeof(int));
}

static IRBuilder *createDumpVisitor(IRBuilder *builder)
{
#define DEFINE_BUILDER_API(NAME) builder->api.visit##NAME = DumpVisitor_visit##NAME;
	VISITOR_LIST(DEFINE_BUILDER_API);
#undef DEFINE_BUILDER_API
	builder->api.fn_Init = DumpVisitor_Init;
	builder->api.fn_Free = DumpVisitor_Free;
	return builder;
}

#ifdef __cplusplus
}
#endif

#undef DUMPER
#endif /* USE_DUMP_VISITOR */
