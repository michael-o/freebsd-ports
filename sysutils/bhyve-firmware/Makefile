PORTNAME=	bhyve-firmware
PORTVERSION=	1.0
PORTREVISION=	2
CATEGORIES=	sysutils

MAINTAINER=	fabian.freyer@physik.tu-berlin.de
COMMENT=	Collection of Firmware for bhyve
WWW=		https://wiki.freebsd.org/bhyve/UEFI

RUN_DEPENDS=	${LOCALBASE}/share/uefi-firmware/BHYVE_UEFI_CODE.fd:sysutils/edk2@bhyve \
		${LOCALBASE}/share/edk2-legacy-bhyve/BHYVE_UEFI_CODE.fd:sysutils/edk2-legacy@bhyve

USES=		metaport

.include <bsd.port.mk>
