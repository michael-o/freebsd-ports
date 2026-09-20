PORTNAME=	scikit-learn
DISTVERSION=	1.9.1
CATEGORIES=	science python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}
DISTNAME=	scikit_learn-${DISTVERSION}

MAINTAINER=	wen@FreeBSD.org
COMMENT=	Machine learning algorithms for python
WWW=		https://scikit-learn.org/

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}meson-python>=0.17.1:devel/meson-python@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numpy>=2:math/py-numpy@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}scipy>=1.11.4:science/py-scipy@${PY_FLAVOR}
RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}joblib>=1.4.0:devel/py-joblib@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}narwhals>=2.0.1:math/py-narwhals@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}numpy>=1.26.0:math/py-numpy@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}scipy>=1.11.4:science/py-scipy@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}threadpoolctl>=3.5.0:devel/py-threadpoolctl@${PY_FLAVOR}

USES=		fortran python localbase shebangfix
USE_PYTHON=	autoplist cython pep517 pytest

TEST_ARGS=	sklearn
TEST_WRKSRC=	${STAGEDIR}${PYTHON_SITELIBDIR}

SHEBANG_FILES=	sklearn/_build_utils/version.py
BINARY_ALIAS=	cython=cython-${PYTHON_VER}

post-install: # strip binaries
	@${STRIP_CMD} \
		${STAGEDIR}${PYTHON_SITELIBDIR}/sklearn/*.cpython*.so \
		${STAGEDIR}${PYTHON_SITELIBDIR}/sklearn/*/*.cpython*.so \
		${STAGEDIR}${PYTHON_SITELIBDIR}/sklearn/*/*/*.cpython*.so

.include <bsd.port.mk>
