PORTNAME=	sqlcipher3
DISTVERSION=	0.6.2
CATEGORIES=	databases python
#MASTER_SITES=	PYPI # no tests
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	yuri@FreeBSD.org
COMMENT=	Python 3 bindings for SQLCipher
WWW=		https://github.com/coleifer/sqlcipher3

LICENSE=	ZLIB
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}setuptools>=63.0:devel/py-setuptools@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}wheel>=0:devel/py-wheel@${PY_FLAVOR}

LIB_DEPENDS=	libsqlcipher.so:databases/sqlcipher

USES=		localbase python ssl
USE_PYTHON=	autoplist pep517

USE_GITHUB=	yes
GH_ACCOUNT=	coleifer

TEST_ENV=	${MAKE_ENV} PYTHONPATH=${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}

post-install:
	@${STRIP_CMD} ${STAGEDIR}${PYTHON_SITELIBDIR}/sqlcipher3/_sqlite3${PYTHON_TAG}.so

do-test:
	@cd ${WRKSRC} && \
		${CP} ${STAGEDIR}${PYTHON_SITELIBDIR}/sqlcipher3/_sqlite3${PYTHON_TAG}.so sqlcipher3/ && \
		${SETENV} ${TEST_ENV} ${PYTHON_CMD} -m tests

# tests as of 0.6.0:
# Ran 345 tests in 0.241s
#
# OK (skipped=2)

.include <bsd.port.mk>
