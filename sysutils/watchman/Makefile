PORTNAME=	watchman
DISTVERSIONPREFIX=	v
DISTVERSION=	2026.10.05.00
CATEGORIES=	sysutils

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	File alteration monitoring service
WWW=		https://facebook.github.io/watchman/

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	googletest>0:devel/googletest
LIB_DEPENDS=	libboost_context.so:devel/boost-libs \
		libboost_filesystem.so:devel/boost-libs \
		libboost_program_options.so:devel/boost-libs \
		libboost_regex.so:devel/boost-libs \
		libbzip2.so:misc/vxl \
		libedencommon_utils.so:devel/edencommon \
		libevent.so:devel/libevent \
		libfb303.so:net/fb303 \
		libfizz.so:security/fizz \
		libfmt.so:devel/libfmt \
		libfolly.so:devel/folly \
		libgflags.so:devel/gflags \
		libglog.so:devel/glog \
		liblz4.so:archivers/liblz4 \
		libmvfst.so:net/mvfst \
		libsnappy.so:archivers/snappy \
		libsodium.so:security/libsodium \
		libthriftcpp2.so:devel/fbthrift \
		libunwind.so:devel/libunwind \
		libwangle.so:net/wangle \
		libxxhash.so:devel/xxhash \
		libzstd.so:archivers/zstd

USES=		cmake:testing compiler:c++20-lang ssl

USE_GITHUB=	yes
GH_ACCOUNT=	facebook

CMAKE_ARGS=	-DWATCHMAN_VERSION_OVERRIDE=${DISTVERSION} \
		-DWATCHMAN_STATE_DIR=/var/run/${PORTNAME}
CMAKE_OFF=	ENABLE_EDEN_SUPPORT

PLIST_FILES=	bin/${PORTNAME} \
		"@dir(,,2777) /var/run/${PORTNAME}"

OPTIONS_DEFINE=	BACKTRACE PCRE DOCS
OPTIONS_DEFAULT=BACKTRACE PCRE

BACKTRACE_DESC=		Stack backtrace support via (lib)execinfo
BACKTRACE_LDFLAGS=	-lexecinfo
DOCS_PLIST_FILES=	${DOCSDIR}/README.markdown
PCRE_LIB_DEPENDS=	libpcre2-8.so:devel/pcre2

post-install:
	@${MKDIR} ${STAGEDIR}/var/run/${PORTNAME}

post-install-DOCS-on:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/README.markdown ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
