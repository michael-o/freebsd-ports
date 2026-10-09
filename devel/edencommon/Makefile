PORTNAME=	edencommon
DISTVERSIONPREFIX=	v
DISTVERSION=	2026.10.05.00
CATEGORIES=	devel

MAINTAINER=	michaelo@FreeBSD.org
COMMENT=	Shared utility library for Watchman and EdenFS
WWW=		https://github.com/facebookexperimental/edencommon

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libboost_context.so:devel/boost-libs \
		libboost_filesystem.so:devel/boost-libs \
		libboost_program_options.so:devel/boost-libs \
		libboost_regex.so:devel/boost-libs \
		libbzip2.so:misc/vxl \
		libevent.so:devel/libevent \
		libfb303.so:net/fb303 \
		libfizz.so:security/fizz \
		libfmt.so:devel/libfmt \
		libfolly.so:devel/folly \
		libgflags.so:devel/gflags \
		libglog.so:devel/glog \
		libgmock.so:devel/googletest \
		libgmock_main.so:devel/googletest \
		libgtest.so:devel/googletest \
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
GH_ACCOUNT=	facebookexperimental
USE_LDCONFIG=	yes

CMAKE_ON=	BUILD_SHARED_LIBS

.include <bsd.port.mk>
