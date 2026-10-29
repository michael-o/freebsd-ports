PKGNAMEPREFIX=	java-

MAINTAINER=	michaelo@apache.org
COMMENT=	Java bindings for Apache Subversion
WWW=		https://subversion.apache.org/

USES=		java
JAVA_OS=	native

PORTREVISION_LATEST=	0
PORTREVISION_LTS=		3

.include "${.CURDIR}/../../devel/subversion/Makefile.addons"

CATEGORIES+=	java

BUILD_DEPENDS+=	${JAVAJARDIR}/junit.jar:java/junit
LIB_DEPENDS+=	libserf-1.so:www/serf \
		libapr-1.so:devel/apr1 \
		libaprutil-1.so:devel/apr1 \
		libsqlite3.so:databases/sqlite3 \
		libexpat.so:textproc/expat2 \
		libutf8proc.so:textproc/utf8proc \
		liblz4.so:archivers/liblz4
.if ${WITH_SUBVERSION_VER:U} == LTS
LIB_DEPENDS+=	libsvn_fs_x-1.so:devel/subversion-lts \
		libsvn_fs_util-1.so:devel/subversion-lts
.else
LIB_DEPENDS+=	libsvn_fs_x-1.so:devel/subversion \
		libsvn_fs_util-1.so:devel/subversion
.endif

CONFIGURE_ARGS+=	--enable-javahl \
			--with-junit=${JAVAJARDIR}/junit.jar \
			--without-swig-perl \
			--without-swig-python \
			--without-swig-ruby \
			--with-jdk=${JAVA_HOME} \
			--with-jikes=no \
			--without-gnome-keyring \
			--without-kwallet \
			--with-apxs=no \
			--disable-nls

# real race: build.conf's Java-target add-deps only threads into the
# phony aggregate target, not the javac -h compile rule itself, so -j
# can run javahl-types-java before javahl-java's NativeResources.class
# exists ("cannot find symbol: variable NativeResources")
MAKE_JOBS_UNSAFE=	yes

ALL_TARGET=	javahl
INSTALL_TARGET=	install-javahl

pre-configure:
	${REINPLACE_CMD} "s#^javahl_javadir = .*#javahl_javadir = ${JAVAJARDIR}#" ${WRKSRC}/Makefile.in

pre-build:
	@${MKDIR} ${WRKSRC}/subversion/bindings/java/javahl/classes

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libsvnjavahl-1.so.0.0.0
	${RM} ${STAGEDIR}${PREFIX}/lib/libsvnjavahl-1.a

.include <bsd.port.post.mk>
