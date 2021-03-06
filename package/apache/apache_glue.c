/****************************************************************************
 * Copyright (c) 2012, the Konoha project authors. All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
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

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "http_log.h"
#include "ap_config.h"
#include "apr_strings.h"
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_VERSION
#include "apache_glue.h"

#ifdef __cplusplus
extern "C"{
#endif


static void Request_Init(KonohaContext *kctx, kObject *po, void *conf)
{
	(void)kctx;
	((kRequest *)po)->r = (request_rec *) conf;
}

static void Request_Free(KonohaContext *kctx, kObject *po)
{
	(void)kctx;
((kRequest *)po)->r = NULL;
}

static void AprTable_Init(KonohaContext *kctx, kObject *po, void *conf)
{
	(void)kctx;
	((kAprTable *)po)->tbl = (apr_table_t *) conf;
}

static void AprTable_Free(KonohaContext *kctx, kObject *po)
{
	(void)kctx;
	((kAprTable *)po)->tbl = NULL;
}

static void AprTableEntry_Init(KonohaContext *kctx, kObject *po, void *conf)
{
	(void)kctx;
	((kAprTableEntry *)po)->entry = (apr_table_entry_t *) conf;
}

static void AprTableEntry_Free(KonohaContext *kctx, kObject *po)
{
	(void)kctx;
	((kAprTableEntry *)po)->entry = NULL;
}

static void kapacheshare_Setup(KonohaContext *kctx, struct KonohaModule *def, int newctx) {}
static void kapacheshare_Reftrace(KonohaContext *kctx, struct KonohaModule *baseh, KObjectVisitor *visitor) {}
static void kapacheshare_Free(KonohaContext *kctx, struct KonohaModule *baseh)
{
	KFree(baseh, sizeof(kapacheshare_t));
}


static kbool_t apache_PackupNameSpace(KonohaContext *kctx, kNameSpace *ns, int option, KTraceInfo *trace)
{
	static KDEFINE_CLASS Def = {
		STRUCTNAME(Request),
		.init = Request_Init,
		.free = Request_Free,
	};

	static KDEFINE_CLASS aprTableDef = {
		STRUCTNAME(AprTable),
		.init = AprTable_Init,
		.free = AprTable_Free,
	};

	static KDEFINE_CLASS aprTableEntryDef = {
		STRUCTNAME(AprTableEntry),
		.init = AprTableEntry_Init,
		.free = AprTableEntry_Free,
	};

	static KDEFINE_CLASS apacheDef = {
		STRUCTNAME(Apache),
	};

	kapacheshare_t *base = (kapacheshare_t *)KCalloc_UNTRACE(sizeof(kapacheshare_t), 1);
	base->h.name     = "apache";
	base->h.setup    = kapacheshare_Setup;
	base->h.reftrace = kapacheshare_Reftrace;
	base->h.free     = kapacheshare_Free;
	KLIB KonohaRuntime_setModule(kctx, MOD_APACHE, &base->h, trace);
	base->cRequest = KLIB kNameSpace_DefineClass(kctx, ns, NULL, &Def, 0);
	base->cAprTable = KLIB kNameSpace_DefineClass(kctx, ns, NULL, &aprTableDef, 0);
	base->cAprTableEntry = KLIB kNameSpace_DefineClass(kctx, ns, NULL, &aprTableEntryDef, 0);
	base->cApache = KLIB kNameSpace_DefineClass(kctx, ns, NULL, &apacheDef, 0);

	KDEFINE_INT_CONST IntData[] = {
#define DEFINE_KEYWORD(KW) {#KW, TY_int, KW}
		{"APACHE_OK", TY_int, OK},
		{"APLOG_EMERG", TY_int, APLOG_EMERG},
		{"APLOG_ALERT", TY_int, APLOG_ALERT},
		{"APLOG_CRIT", TY_int, APLOG_CRIT},
		{"APLOG_ERR", TY_int, APLOG_ERR},
		{"APLOG_WARNING", TY_int, APLOG_WARNING},
		{"APLOG_NOTICE", TY_int, APLOG_NOTICE},
		{"APLOG_INFO", TY_int, APLOG_INFO},
		{"APLOG_DEBUG", TY_int, APLOG_DEBUG},
		{NULL, 0, 0}
	};
	KLIB kNameSpace_LoadConstData(kctx, ns, KonohaConst_(IntData), 0);
	return true;
}

static kbool_t apache_ExportNameSpace(KonohaContext *kctx, kNameSpace *ns, kNameSpace *exportNS, int option, KTraceInfo *trace)
{
	return true;
}

KDEFINE_PACKAGE* apache_Init(void)
{
	static KDEFINE_PACKAGE d = {
		KPACKNAME("apache", "1.0"),
		.PackupNameSpace    = apache_PackupNameSpace,
		.ExportNameSpace   = apache_ExportNameSpace,
	};
	return &d;
}

#ifdef __cplusplus
}
#endif
