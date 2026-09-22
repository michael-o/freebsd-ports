PORTNAME=	pywatchman
DISTVERSIONPREFIX=v
DISTVERSION=	2026.09.21.00
CATEGORIES=	sysutils python
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	rottlogg@proton.me
COMMENT=	Watchman client for Python
WWW=		https://pypi.org/project/pywatchman/

LICENSE=	BSD3CLAUSE MIT
LICENSE_COMB=	multi


BUILD_DEPENDS=	${PY_SETUPTOOLS} \
		${PYTHON_PKGNAMEPREFIX}wheel>=0:devel/py-wheel@${PY_FLAVOR}
RUN_DEPENDS=	watchman>=4:sysutils/watchman

USES=		python
USE_GITHUB=	yes
GH_ACCOUNT=	facebook
GH_PROJECT=	watchman
USE_PYTHON=	autoplist concurrent pep517 pytest

WRKSRC_SUBDIR=	watchman/python

post-install:
	${FIND} ${STAGEDIR}${PYTHON_SITELIBDIR} -name "*.so" \
		-exec ${STRIP_CMD} {} +

.include <bsd.port.mk>
