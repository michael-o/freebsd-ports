PORTNAME=	edk2-tools
PORTVERSION=	g202605
CATEGORIES=	devel

PATCH_SITES=	https://github.com/${GH_ACCOUNT}/${GH_PROJECT}/commit/

MAINTAINER=	alex@paidbsd.org
COMMENT=	Utilities from EDK2
WWW=		https://github.com/${GH_ACCOUNT}/${GH_PROJECT}/

LICENSE=	BSD3CLAUSE

USES=		gmake python:build python:run

USE_GITHUB=	yes
GH_ACCOUNT=	tianocore
GH_PROJECT=	edk2
GH_TAGNAME=	edk2-stable202605

GH_TUPLE= google:brotli:e230f474b87134e8c6c85b630084c612057f253e:brotli/BaseTools/Source/C/BrotliCompress/brotli

.include <bsd.port.pre.mk>

BINARY_ALIAS=	make=${GMAKE} \
		python3=${PYTHON_CMD} python=${PYTHON_CMD} \

TOOLSRC= ${WRKSRC}/BaseTools/Source
TOOLIN= ${STAGEDIR}${PREFIX}/libexec/${PORTNAME}

SUB_FILES= pkg-message
SUB_LIST= PORTNAME=${PORTNAME}

MAKE_ENV=	PYTHON_COMMAND=${PYTHON_CMD}

# Building with only one job else VfrCompiler breaks once every 20 or so builds
# (There's a race condidion in template processing there, yuck!)
do-build:
	( \
		export ${MAKE_ENV} && \
		cd ${TOOLSRC}/.. && \
		${MAKE_CMD} -j1 \
	)

do-install:
	${MKDIR} ${TOOLIN}
	${CP} -a ${TOOLSRC}/C/bin ${TOOLIN}/C
	# C utilities are fine in PATH
	for bin in ${TOOLIN}/C/*; do \
		${RLN} $${bin} ${STAGEDIR}${PREFIX}/bin/; \
	done
	# Clean up Python dir
	${FIND} ${TOOLSRC}/Python \(\
	       -name __pycache__ -o \
	       -name GNUmakefile -o \
	       -name Makefile -o \
	       -name tests \) -exec ${RM} -r -- {} +
	${CP} -a ${TOOLSRC}/Python ${TOOLIN}/Python

.include <bsd.port.post.mk>
