PORTNAME=	wsgidav
DISTVERSION=	4.3.5
CATEGORIES=	www python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	chris.longros@gmail.com
COMMENT=	WSGI-based WebDAV server for sharing resources
WWW=		https://github.com/mar10/wsgidav

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}setuptools>=0:devel/py-setuptools@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}wheel>=0:devel/py-wheel@${PY_FLAVOR}
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}bcrypt>=4.0:security/py-bcrypt@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}defusedxml>=0.7.1:devel/py-defusedxml@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}Jinja2>=3.1:devel/py-Jinja2@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}json5>=0.14:devel/py-json5@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}passlib>=1.7:security/py-passlib@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyyaml>=6.0:devel/py-pyyaml@${PY_FLAVOR}
TEST_DEPENDS=	${PYTHON_PKGNAMEPREFIX}cheroot>=0:www/py-cheroot@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}requests>=0:www/py-requests@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}webtest>=0:www/py-webtest@${PY_FLAVOR}

USES=		python
USE_PYTHON=	autoplist concurrent pep517 pytest

NO_ARCH=	yes
# NOTE: In order to run tests, need to switch to the GitHub repo, else will
# succeed with 0 test runs.
NO_TEST=	yes

OPTIONS_DEFINE=	LXML PAM

LXML_DESC=	Use lxml XML parser
PAM_DESC=	PAM authentication support

LXML_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}lxml>=0:devel/py-lxml@${PY_FLAVOR}

PAM_RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}python-pam>=0:security/py-python-pam@${PY_FLAVOR}

.include <bsd.port.mk>
