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

#include<minikonoha/minikonoha.h>
#include<minikonoha/sugar.h>
//#include<minikonoha/float.h>

// operator only
//#include"assign_glue.h"
//#include"while_glue.h"

// class and operator
//#include"class_glue.h"
//#include"global_glue.h"

// method and operator
//#include"array_glue.h"


// --------------------------------------------------------------------------

static	kbool_t konoha_initPackage(KonohaContext *kctx, kNameSpace *ns, int argc, const char**args, kfileline_t pline)
{
	KRequirePackage("konoha.assign", pline);
	KRequirePackage("konoha.while", pline);

	KRequirePackage("konoha.class", pline);
	KRequirePackage("konoha.global", pline);

	KRequirePackage("konoha.null", pline);
	KRequirePackage("konoha.int", pline);
#ifndef K_USING_NOFLOAT
	KRequirePackage("konoha.float", pline);
#endif
	KRequirePackage("konoha.array", pline);
	return true;
}

static kbool_t konoha_setupPackage(KonohaContext *kctx, kNameSpace *ns, isFirstTime_t isFirstTime, kfileline_t pline)
{
	return true;
}

static kbool_t konoha_initNameSpace(KonohaContext *kctx, kNameSpace *packageNameSpace, kNameSpace *ns, kfileline_t pline)
{
	KImportPackage(ns, "konoha.assign", pline);
	KImportPackage(ns, "konoha.while",  pline);
	KImportPackage(ns, "konoha.class",  pline);
	KImportPackage(ns, "konoha.global", pline);

	KImportPackage(ns, "konoha.null", pline);
	KImportPackage(ns, "konoha.int",  pline);
	if(kctx->modshare[MOD_float] != NULL) {
		KImportPackage(ns, "konoha.float", pline);
	}
	KImportPackage(ns, "konoha.array", pline);
	return true;
}

static kbool_t konoha_setupNameSpace(KonohaContext *kctx, kNameSpace *packageNameSpace, kNameSpace *ns, kfileline_t pline)
{
	return true;
}

KDEFINE_PACKAGE* konoha_init(void)
{
	static KDEFINE_PACKAGE d = {
		KPACKNAME("konoha", "1.0"),
		.initPackage = konoha_initPackage,
		.setupPackage = konoha_setupPackage,
		.initNameSpace = konoha_initNameSpace,
		.setupNameSpace = konoha_setupNameSpace,
	};
	return &d;
}

