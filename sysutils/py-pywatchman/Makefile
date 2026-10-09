PORTNAME=	pywatchman
DISTVERSIONPREFIX=	v
DISTVERSION=	2026.10.05.00
CATEGORIES=	sysutils python
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

# setuptools normalizes the version string per PEP 440 (strips leading
# zeros from each dot-separated segment: 2026.10.05.00 -> 2026.10.5.0),
# so the wheel it produces -- and therefore its filename and
# .dist-info/RECORD path -- uses this normalized form, not DISTVERSION
# itself. Mk/Uses/python.mk's PEP517 install logic globs on literal
# ${DISTVERSION}, so override PEP517_INSTALL_CMD/the RECORD lookup to
# glob on the normalized string instead of patching DISTVERSION itself
# (which would also perturb GH_TAGNAME_DEFAULT/DISTFILES naming).
PEP517_VERSION=	${DISTVERSION:C/\.0+([0-9])/.\1/g}

MAINTAINER=	rottlogg@proton.me
COMMENT=	Watchman client for Python
WWW=		https://facebook.github.io/watchman/

LICENSE=	BSD3CLAUSE MIT
LICENSE_COMB=	multi

BUILD_DEPENDS=	${PYTHON_PKGNAMEPREFIX}setuptools>=61.0:devel/py-setuptools@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}wheel>=0.37.0:devel/py-wheel@${PY_FLAVOR}
RUN_DEPENDS=	watchman>=4:sysutils/watchman

USES=		python
USE_GITHUB=	yes
GH_ACCOUNT=	facebook
GH_PROJECT=	watchman
USE_PYTHON=	autoplist pep517 unittest

WRKSRC_SUBDIR=	watchman/python

TEST_ARGS=	tests.tests

# PEP 517 only builds the bser C extension inside the wheel in dist/,
# not in-place under pywatchman/. python -m unittest runs with cwd =
# WRKSRC, so without an in-place build it resolves pywatchman/bser.so
# as missing and silently falls back to pybser -- which tests.py
# explicitly guards against and fails loudly on. setup.py's own
# "test" subcommand used to paper over this (it ran build_ext
# --inplace as a side effect before running tests); build_ext itself
# is still fully supported, only "test" was removed from setuptools.
pre-test:
	@cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${PYTHON_CMD} setup.py build_ext --inplace

# Mk/Uses/python.mk's PEP517_INSTALL_CMD default globs dist/${PORTNAME}-
# ${DISTVERSION}*.whl; point it at the normalized version instead so it
# actually finds the wheel setuptools produced.
PEP517_INSTALL_CMD=	${PYTHON_CMD} -m installer --destdir ${STAGEDIR} \
			--prefix ${PREFIX} \
			${BUILD_WRKSRC}/dist/${PORTNAME:C|[-_]+|_|g}-${PEP517_VERSION}*.whl

# pyproject.toml hardcodes a version that upstream only bumps for PyPI
# publication, which lags the GitHub source this port actually builds
# from -- rewrite it to the version we're actually building so it's not
# a lie, and so the installed package's own metadata is self-consistent.
# Written already-PEP-440-normalized (see PEP517_VERSION above), since
# that's the only form setuptools would accept unchanged.
post-patch:
	@${REINPLACE_CMD} -e 's/^version = ".*"/version = "${PEP517_VERSION}"/' \
		${WRKSRC}/pyproject.toml

# Mirrors Mk/Uses/python.mk's own do-install for the PEP517 case, with
# the .dist-info/RECORD glob pointed at the normalized version (see
# PEP517_INSTALL_CMD override above for why).
do-install:
	@${MKDIR} ${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}
	@cd ${INSTALL_WRKSRC} && ${SETENVI} ${WRK_ENV} ${MAKE_ENV} ${PEP517_INSTALL_CMD}
	@${PYTHON_CMD} -B ${PORTSDIR}/Mk/Scripts/strip_RECORD.py \
		${STAGEDIR}${PYTHONPREFIX_SITELIBDIR}/${PORTNAME:C|[-_]+|_|g}-${PEP517_VERSION}*.dist-info/RECORD >> ${_PYTHONPKGLIST}
	@${REINPLACE_CMD} \
		-e '/\.pyc$$/d' \
		-e 's|^|${PYTHONPREFIX_SITELIBDIR}/|' \
		-e 's|^${PYTHONPREFIX_SITELIBDIR}/../../../etc/|etc/|' \
		-e 's|^${PYTHONPREFIX_SITELIBDIR}/../../../bin/|bin/|' \
		-e 's|^${PYTHONPREFIX_SITELIBDIR}/../../../include/|include/|' \
		-e 's|^${PYTHONPREFIX_SITELIBDIR}/../../../lib/|lib/|' \
		-e 's|^${PYTHONPREFIX_SITELIBDIR}/../../../libdata/|libdata/|' \
		-e 's|^${PYTHONPREFIX_SITELIBDIR}/../../../libexec/|libexec/|' \
		-e 's|^${PYTHONPREFIX_SITELIBDIR}/../../../man/|man/|' \
		-e 's|^${PYTHONPREFIX_SITELIBDIR}/../../../sbin/|sbin/|' \
		-e 's|^${PYTHONPREFIX_SITELIBDIR}/../../../share/|share/|' \
			${_PYTHONPKGLIST}
	@cd ${STAGEDIR}${PREFIX} && ${FIND} lib -name '*.pyc' >> ${_PYTHONPKGLIST}

post-install:
	${FIND} ${STAGEDIR}${PYTHON_SITELIBDIR} -name "*.so" \
		-exec ${STRIP_CMD} {} +

.include <bsd.port.mk>
