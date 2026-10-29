PORTNAME=	mod_dav_svn
DISTNAME=	subversion-${PORTVERSION}

CATEGORIES=	www

MAINTAINER=	michaelo@apache.org
COMMENT=	Apache HTTP Server modules for Apache Subversion
WWW=		https://subversion.apache.org/

DEPRECATED=	Superseded by www/mod_subversion for devel/subversion (latest); \
		kept only for devel/subversion-lts users

CONFLICTS_INSTALL=	mod_subversion

USES=		apache

PORTREVISION_LATEST=	0
PORTREVISION_LTS=		1

.include "${.CURDIR}/../../devel/subversion/Makefile.addons"

CONFIGURE_ARGS+=	--with-apxs=${APXS} \
			--with-apache-libexecdir \
			--without-gnome-keyring \
			--without-kwallet \
			--disable-nls
SUB_FILES+=	220_subversion.conf.sample

ALL_TARGET=	apache-mod
INSTALL_TARGET=	install-mods-shared

post-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/${APACHEETCDIR}/modules.d
	${INSTALL_DATA} ${WRKDIR}/220_subversion.conf.sample \
		${STAGEDIR}${PREFIX}/${APACHEETCDIR}/modules.d
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/${APACHEMODDIR}/mod_dav_svn.so \
		${STAGEDIR}${PREFIX}/${APACHEMODDIR}/mod_authz_svn.so \
		${STAGEDIR}${PREFIX}/${APACHEMODDIR}/mod_dontdothat.so

.include <bsd.port.post.mk>
