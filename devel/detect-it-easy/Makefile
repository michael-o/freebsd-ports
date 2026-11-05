PORTNAME=	detect-it-easy
DISTVERSION=	3.21
CATEGORIES=	devel
MASTER_SITES=	https://github.com/horsicq/DIE-engine/releases/download/${DISTVERSION}/
DISTNAME=	die_sourcecode_${DISTVERSION}

MAINTAINER=	res2500@ukr.net
COMMENT=	File type identification and binary analysis utility
WWW=		https://github.com/horsicq/Detect-It-Easy

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		compiler:c++17-lang desktop-file-utils dos2unix gl qmake qt:6

DOS2UNIX_FILES=	XOptions/xoptions.cpp

USE_GL=		gl
USE_QT=		5compat base declarative svg tools:build

CXXFLAGS+=	-Wno-register

DIE_BINDIR=	${WRKSRC}/build/release
DIE_DATADIR=	${STAGEDIR}${PREFIX}/share/die

do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/bin
	${INSTALL_PROGRAM} ${DIE_BINDIR}/die \
		${STAGEDIR}${PREFIX}/bin/die
	${INSTALL_PROGRAM} ${DIE_BINDIR}/diec \
		${STAGEDIR}${PREFIX}/bin/diec
	${INSTALL_PROGRAM} ${DIE_BINDIR}/diel \
		${STAGEDIR}${PREFIX}/bin/diel

	${MKDIR} ${DIE_DATADIR}/signatures

	(cd ${WRKSRC}/Detect-It-Easy && \
		${COPYTREE_SHARE} db ${DIE_DATADIR})
	(cd ${WRKSRC}/Detect-It-Easy && \
		${COPYTREE_SHARE} db_extra ${DIE_DATADIR})
	(cd ${WRKSRC}/Detect-It-Easy && \
		${COPYTREE_SHARE} db_custom ${DIE_DATADIR})

	(cd ${WRKSRC}/XYara && \
		${COPYTREE_SHARE} yara_rules ${DIE_DATADIR})
	(cd ${WRKSRC}/XPEID && \
		${COPYTREE_SHARE} peid ${DIE_DATADIR})
	(cd ${WRKSRC}/XStyles && \
		${COPYTREE_SHARE} qss ${DIE_DATADIR})
	(cd ${WRKSRC}/XInfoDB && \
		${COPYTREE_SHARE} info ${DIE_DATADIR})
	(cd ${WRKSRC} && \
		${COPYTREE_SHARE} images ${DIE_DATADIR})

	${INSTALL_DATA} ${WRKSRC}/signatures/crypto.db \
		${DIE_DATADIR}/signatures/crypto.db

	${FIND} ${DIE_DATADIR} -type d -name .vscode \
		-prune -exec ${RM} -r {} +

	${MKDIR} ${STAGEDIR}${PREFIX}/share/applications
	${INSTALL_DATA} \
		${WRKSRC}/LINUX/io.github.horsicq.detect-it-easy.desktop \
		${STAGEDIR}${PREFIX}/share/applications/

	${MKDIR} ${STAGEDIR}${PREFIX}/share/icons
	(cd ${WRKSRC}/LINUX && \
		${COPYTREE_SHARE} hicolor ${STAGEDIR}${PREFIX}/share/icons)

	${MKDIR} ${STAGEDIR}${PREFIX}/share/metainfo
	${INSTALL_DATA} \
		${WRKSRC}/LINUX/io.github.horsicq.detect-it-easy.metainfo.xml \
		${STAGEDIR}${PREFIX}/share/metainfo/

.include <bsd.port.mk>
