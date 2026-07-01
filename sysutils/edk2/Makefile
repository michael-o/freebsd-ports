PORTNAME=	edk2
PORTVERSION=	g202605
CATEGORIES=	sysutils
PKGNAMESUFFIX=	-${FLAVOR:C/_/-/g}

PATCH_SITES=	https://github.com/${GH_ACCOUNT}/${GH_PROJECT}/commit/

MAINTAINER=	uboot@FreeBSD.org
COMMENT=	EDK2 Firmware for ${PLAT_WHATFOR}
WWW=		https://github.com/${GH_ACCOUNT}/${GH_PROJECT}/

LICENSE=	BSD3CLAUSE

ONLY_FOR_ARCHS=		amd64 aarch64
ONLY_FOR_ARCHS_REASON=	Only provides firmware for AMD64 and AARCH64

# Rely on the LLVM port because we don't know whether the
# host LLVM supports the target firmware architecture (compiling AARCH64 firmware on AMD64)
BUILD_DEPENDS=	dtc>=1.4.1:sysutils/dtc \
		bash:shells/bash \
		edk2-tools>=${PORTVERSION}:devel/edk2-tools

FLAVORS=	bhyve xen_x64 xen_aarch64 qemu_x64 qemu_aarch64 macchiatobin fvp rpi3 rpi4
FLAVOR?= 	${FLAVORS:[1]}

# USES=llvm breaks BaseTools build but we do it in a separate package so it's fine.
USES=		cpe gmake python:build llvm:${LLVM_DEFAULT},build
CPE_VENDOR=	tianocore

# Both platforms and non-osi repositories don't use releases, so we use latest known to work tag
PLATFORMS_TAG=	f37b334aad56fff58bbc1169983657a3167377ce # 2026-05-26
NONOSI_TAG=	7ac12d81e02b323bffdf1ef3c188ea33c2185c91 # 2026-04-02

USE_GITHUB=	yes
GH_PROJECT=	edk2
GH_ACCOUNT=	tianocore
GH_TAGNAME=	edk2-stable202605

PATCH_SITES= https://github.com/${GH_ACCOUNT}/${GH_PROJECT}/commit/

GH_TUPLE= tianocore:edk2-platforms:${PLATFORMS_TAG}:platforms/PlatformsPkg \
	tianocore:edk2-non-osi:${NONOSI_TAG}:nonosi/NonOsiPkg \
	tianocore:edk2-cmocka:1cc9cde3448cdd2e000886a26acf1caac2db7cf1:edk2_cmocka/UnitTestFrameworkPkg/Library/CmockaLib/cmocka \
	tianocore:edk2-subhook:83d4e1ebef3588fae48b69a7352cc21801cb70bc:edk2_subhook/UnitTestFrameworkPkg/Library/SubhookLib/subhook \
	ARMmbed:mbedtls:0bebf8b8c7f07abe3571ded48a11aa907a1ffb20:mbedtls/CryptoPkg/Library/MbedTlsLib/mbedtls \
	DMTF:libspdm:1be116c7b7713fa9003e1bd53b53a34758549eb9:libspdm/SecurityPkg/DeviceSecurity/SpdmLib/libspdm \
	MIPI-Alliance:public-mipi-sys-t:370b5944c046bab043dd8b133727b2135af7747a:public_mipi_sys_t/MdePkg/Library/MipiSysTLib/mipisyst \
	TrustedComputingGroup:TPM:bc29a21d44b01396223c152a4834e52318591770:TPM/TcgTpmPkg/Library/TpmLib/TPM \
	akheron:jansson:e9ebfa7e77a6bee77df44e096b100e7131044059:jansson/RedfishPkg/Library/JsonLib/jansson \
	devicetree-org:pylibfdt:cfff805481bdea27f900c32698171286542b8d3c:pylibfdt/MdePkg/Library/BaseFdtLib/libfdt \
	google:brotli:e230f474b87134e8c6c85b630084c612057f253e:brotli/MdeModulePkg/Library/BrotliCustomDecompressLib/brotli \
	google:googletest:86add13493e5c881d7e4ba77fb91c1f57752b3a4:googletest/UnitTestFrameworkPkg/Library/GoogleTestLib/googletest \
	kkos:oniguruma:4ef89209a239c1aea328cf13c05a2807e5c146d1:oniguruma/MdeModulePkg/Universal/RegularExpressionDxe/oniguruma \
	openssl:openssl:aea7aaf2abb04789f5868cbabec406ea43aa84bf:openssl/CryptoPkg/Library/OpensslLib/openssl

.include <bsd.port.pre.mk>

# BINARY_ALIAS continues below after flavors
BINARY_ALIAS=	make=${GMAKE} \
		dtc=${LOCALBASE}/bin/dtc \
		python3=${PYTHON_CMD} python=${PYTHON_CMD}

# Global args
PLAT_ARGS=	-D NETWORK_ENABLE=TRUE -D NETWORK_IP4_ENABLE=TRUE -D NETWORK_IP6_ENABLE=TRUE \
		-D NETWORK_PXE_BOOT_ENABLE=TRUE -D NETWORK_HTTP_BOOT_ENABLE=TRUE -D NETWORK_TLS_ENABLE=TRUE
PLAT_TC=	CLANGDWARF

#
# Try to keep the flavor definitions organized like so:
# ONLY_FOR_ARCHS*
# PATCHFILES
# (Additional make stuff)
#
# PLAT
# PLAT_WHATFOR
#
# PLAT_DSCFILE
# PLAT_ARCH
# PLAT_TARGET
# PLAT_ARGS
#
# PLAT_RESULT*
# PLAT_FILENAME*
#

.if ${FLAVOR} == fvp
PLAT=			fvp
PLAT_WHATFOR=		ARM's Fixed Virtual Platform

PLAT_DSCFILE=		Platform/ARM/VExpressPkg/ArmVExpress-FVP-AArch64.dsc
PLAT_ARCH=		AARCH64
PLAT_TARGET=		RELEASE
PLAT_ARGS+=		-D X64EMU_ENABLE=FALSE -D CAPSULE_ENABLE=FALSE
# Avoid issues with missing TlsDxe in the DSC file (Remove HTTPS boot)
PLAT_ARGS+=		-D NETWORK_HTTP_BOOT_ENABLE=FALSE -D NETWORK_TLS_ENABLE=FALSE

PLAT_RESULT=		ArmVExpress-FVP-AArch64/${PLAT_TARGET}_${PLAT_TC}/FV/FVP_AARCH64_EFI.fd
PLAT_FILENAME=		FVP_AARCH64_EFI.fd
.endif

.if ${FLAVOR} == macchiatobin
PLAT=			macchiatobin
PLAT_WHATFOR=		Marvell MACCHIATObin

PLAT_DSCFILE=		Platform/SolidRun/Armada80x0McBin/Armada80x0McBin.dsc
PLAT_ARCH=		AARCH64
PLAT_TARGET=		RELEASE
PLAT_ARGS+=		-D X64EMU_ENABLE=FALSE -D CAPSULE_ENABLE=FALSE
# Avoid issues with missing TlsDxe in the DSC file (Remove HTTPS boot)
PLAT_ARGS+=		-D NETWORK_HTTP_BOOT_ENABLE=FALSE -D NETWORK_TLS_ENABLE=FALSE

PLAT_RESULT=		Armada80x0McBin-AARCH64/${PLAT_TARGET}_${PLAT_TC}/FV/ARMADA_EFI.fd
PLAT_FILENAME=		ARMADA_EFI.fd
.endif

.if ${FLAVOR} == rpi3
PLAT=			rpi3
PLAT_WHATFOR=		BCM2837-based Raspberry Pis (2B v1.2, 3A+, 3B, 3B+, CM3)

PLAT_DSCFILE=		Platform/RaspberryPi/RPi3/RPi3.dsc
PLAT_ARCH=		AARCH64
PLAT_TARGET=		RELEASE
PLAT_ARGS+=		-D X64EMU_ENABLE=FALSE -D CAPSULE_ENABLE=FALSE

PLAT_RESULT=		RPi3/${PLAT_TARGET}_${PLAT_TC}/FV/RPI_EFI.fd
PLAT_FILENAME=		RPI_EFI.fd
.endif

.if ${FLAVOR} == rpi4
PLAT=			rpi4
PLAT_WHATFOR=	 	BCM2711-based Raspberry Pis (4B, 400)

PLAT_DSCFILE=		Platform/RaspberryPi/RPi4/RPi4.dsc
PLAT_ARCH=		AARCH64
PLAT_TARGET=		RELEASE
PLAT_ARGS+=		-D X64EMU_ENABLE=FALSE -D CAPSULE_ENABLE=FALSE

PLAT_RESULT=		RPi4/${PLAT_TARGET}_${PLAT_TC}/FV/RPI_EFI.fd
PLAT_FILENAME=		RPI_EFI.fd
.endif

# Allow cross build from AARCH64
.if ${FLAVOR} == xen_x64
PLAT=			xen
PLAT_WHATFOR=		the Xen hypervisor (X64)

PLAT_DSCFILE=		OvmfPkg/OvmfXen.dsc
PLAT_ARCH=		X64
PLAT_TARGET=		RELEASE

PLAT_RESULT=		OvmfXen/${PLAT_TARGET}_${PLAT_TC}/FV/OVMF.fd
PLAT_FILENAME=		XEN_${PLAT_ARCH}_EFI.fd
.endif

# Allow cross build from AMD64
.if ${FLAVOR} == xen_aarch64
PLAT=			xen
PLAT_WHATFOR=		the Xen hypervisor (AARCH64)

PLAT_DSCFILE=		ArmVirtPkg/ArmVirtXen.dsc
PLAT_ARCH=		AARCH64
PLAT_TARGET=		RELEASE

PLAT_RESULT=		ArmVirtXen-${PLAT_ARCH}/${PLAT_TARGET}_${PLAT_TC}/FV/XEN_EFI.fd
PLAT_FILENAME=		XEN_${PLAT_ARCH}_EFI.fd
.endif

.if ${FLAVOR} == bhyve
ONLY_FOR_ARCHS=		amd64
ONLY_FOR_ARCHS_REASON=	This firmware is for amd64 bhyve only
# Bring back the shell and iPXE boot, remove SMM (unused), set a one second boot delay
PATCHFILES=		392ef9b5141c45c4ece537dc6667421a508599ad.patch:-p1 \
			ffab4bbcaadd91b7a754a44256fc7538cb35d8a5.patch:-p1 \
			908f0ca66278b37ae091c641189d9421700209d7.patch:-p1

PLAT=			bhyve
PLAT_WHATFOR=		the bhyve hypervisor

PLAT_DSCFILE=		OvmfPkg/Bhyve/BhyveX64.dsc
PLAT_ARCH=		X64
PLAT_TARGET=		RELEASE
PLAT_ARGS+=		-D SECURE_BOOT_ENABLE=TRUE -D TPM2_ENABLE=TRUE

PLAT_RESULT=		BhyveX64/${PLAT_TARGET}_${PLAT_TC}/FV/BHYVE.fd
PLAT_RESULT_CODE=	BhyveX64/${PLAT_TARGET}_${PLAT_TC}/FV/BHYVE_CODE.fd
PLAT_RESULT_VARS=	BhyveX64/${PLAT_TARGET}_${PLAT_TC}/FV/BHYVE_VARS.fd
PLAT_FILENAME=		BHYVE_UEFI.fd
PLAT_FILENAME_CODE=	BHYVE_UEFI_CODE.fd
PLAT_FILENAME_VARS=	BHYVE_UEFI_VARS.fd
.endif

# Fine to compile on AARCH64 since qemu emulates AMD64 there with TCG
.if ${FLAVOR} == qemu_x64
PLAT=			qemu
PLAT_WHATFOR=		the QEMU virtual machine (X64)

PLAT_DSCFILE=		OvmfPkg/OvmfPkgX64.dsc
PLAT_ARCH=		X64
PLAT_TARGET=		RELEASE

PLAT_RESULT=		OvmfX64/${PLAT_TARGET}_${PLAT_TC}/FV/OVMF.fd
PLAT_RESULT_CODE=	OvmfX64/${PLAT_TARGET}_${PLAT_TC}/FV/OVMF_CODE.fd
PLAT_RESULT_VARS=	OvmfX64/${PLAT_TARGET}_${PLAT_TC}/FV/OVMF_VARS.fd
PLAT_FILENAME=		QEMU_UEFI-x86_64.fd
PLAT_FILENAME_CODE=	QEMU_UEFI_CODE-x86_64.fd
PLAT_FILENAME_VARS=	QEMU_UEFI_VARS-x86_64.fd
.endif

# QEMU i386 deprecated upstream, use sysutils/edk2-legacy if you want IA32 OVMF

.if ${FLAVOR} == qemu_aarch64
PLAT=			qemu
PLAT_WHATFOR=		the QEMU virtual machine (AARCH64)

PLAT_DSCFILE=		ArmVirtPkg/ArmVirtQemu.dsc
PLAT_ARCH=		AARCH64
PLAT_TARGET=		RELEASE

PLAT_RESULT=		ArmVirtQemu-AArch64/${PLAT_TARGET}_${PLAT_TC}/FV/QEMU_EFI.fd
PLAT_RESULT_VARS=	ArmVirtQemu-AArch64/${PLAT_TARGET}_${PLAT_TC}/FV/QEMU_VARS.fd
PLAT_FILENAME=		QEMU_UEFI-aarch64.fd
PLAT_FILENAME_VARS=	QEMU_UEFI_VARS-aarch64.fd
.endif

PLIST_FILES=	${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME}
.if defined(PLAT_FILENAME_CODE)
PLIST_FILES+=	${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME_CODE}
.endif
.if defined(PLAT_FILENAME_VARS)
PLIST_FILES+=	${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME_VARS}
.endif

# For sysutils/bhyve-firmware
.if ${FLAVOR} == bhyve
PLIST_FILES+=	${PREFIX}/share/uefi-firmware/${PLAT_FILENAME}
PLIST_FILES+=	${PREFIX}/share/uefi-firmware/${PLAT_FILENAME_CODE}
PLIST_FILES+=	${PREFIX}/share/uefi-firmware/${PLAT_FILENAME_VARS}
.endif

.if ${PLAT_ARCH} == X64
BUILD_DEPENDS+=	nasm:devel/nasm
.endif

# Build variants for GCC and LLVM
# Note that you can't just switch the toolchain as you please, this is here just to
# make sysutils/edk2-legacy (GCC) and sysutils/edk2 (LLVM) use much closer makefiles
# and ease the pain in case EDK2 randomly stops building on LLVM.
.if ${PLAT_TC} == GCC

BINARY_ALIAS+=	gcc=${LOCALBASE}/bin/${CC} \
		g++=${LOCALBASE}/bin/${CXX} \
		nm=${LOCALBASE}/bin/${CC:S/gcc/&-nm/} \
		ar=${LOCALBASE}/bin/${CC:S/gcc/&-ar/} \
		ranlib=${LOCALBASE}/bin/${CC:S/gcc/&-ranlib/} \
		gcc-nm=${LOCALBASE}/bin/${CC:S/gcc/&-nm/} \
		gcc-ar=${LOCALBASE}/bin/${CC:S/gcc/&-ar/} \
		gcc-ranlib=${LOCALBASE}/bin/${CC:S/gcc/&-ranlib/} \

.if ${PLAT_ARCH} == AARCH64 && ${ARCH} != aarch64
BUILD_DEPENDS+=	aarch64-none-elf-gcc:devel/aarch64-none-elf-gcc
MAKE_ENV+=	GCC_AARCH64_PREFIX=aarch64-none-elf-
.endif

.elif ${PLAT_TC} == CLANGDWARF

# Making sure EDK2 is built using the LLVM port and not the host compiler.
BINARY_ALIAS+=	clang=${LOCALBASE}/bin/clang${LLVM_DEFAULT} \
		clang++=${LOCALBASE}/bin/clang++${LLVM_DEFAULT} \
		ar=${LOCALBASE}/bin/llvm-ar${LLVM_DEFAULT} \
		nm=${LOCALBASE}/bin/llvm-nm${LLVM_DEFAULT} \
		ranlib=${LOCALBASE}/bin/llvm-ranlib${LLVM_DEFAULT} \
		ld=${LOCALBASE}/bin/ld.lld${LLVM_DEFAULT}

.endif # PLAT_TC == X

# We don't need EXTRA_LDFLAGS anymore
MAKE_ENV+=	PYTHON_COMMAND=python3 \
		PACKAGES_PATH=${WRKDIR}/edk2-${GH_TAGNAME}:${WRKDIR}/edk2-${GH_TAGNAME}/PlatformsPkg:${WRKDIR}/edk2-${GH_TAGNAME}/NonOsiPkg

# Custom logo for bhyve's OVMF
.if ${FLAVOR} == bhyve
MASTER_SITES+=	LOCAL/dch/bhyve/
DISTFILES+=	BhyveLogo.bmp
EXTRACT_ONLY=	${DISTFILES:M*.gz*:C/.gz:.*/.gz/}
.endif

# Removed copying Brotli to BaseTools as we no longer need to compile it here
post-extract:
.if ${FLAVOR} == bhyve
	# Replace Tianocore logo on bhyve
	(${CP} ${DISTDIR}/BhyveLogo.bmp ${WRKDIR}/edk2-${GH_TAGNAME}/MdeModulePkg/Logo/Logo.bmp)
.endif

do-build:
	# We use devel/edk2-tools so we don't need to compile BaseTools
	# EDK2 still expects them to be in BaseTools/Source/C/bin so just copy them there
	${CP} -a ${LOCALBASE}/libexec/edk2-tools/C ${WRKSRC}/BaseTools/Source/C/bin
	# Run a bash subshell for build
	(bash -c ' \
		export ${MAKE_ENV} && \
		cd ${WRKSRC} && \
		source edksetup.sh && \
		build -a ${PLAT_ARCH} -p ${PLAT_DSCFILE} -n ${MAKE_JOBS_NUMBER} -t ${PLAT_TC} -b ${PLAT_TARGET} ${PLAT_ARGS} \
	')

do-install:
	${MKDIR} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${PLAT}/
	${INSTALL_DATA} ${WRKDIR}/edk2-${GH_TAGNAME}/Build/${PLAT_RESULT} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME}
.if defined(PLAT_FILENAME_CODE)
	${INSTALL_DATA} ${WRKDIR}/edk2-${GH_TAGNAME}/Build/${PLAT_RESULT_CODE} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME_CODE}
.endif
.if defined(PLAT_FILENAME_VARS)
	${INSTALL_DATA} ${WRKDIR}/edk2-${GH_TAGNAME}/Build/${PLAT_RESULT_VARS} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME_VARS}
.endif

.if ${FLAVOR} == bhyve
	# (For now!) bhyve cannot load the merged firmware+vars file so we replace it with raw firmware
	${INSTALL_DATA} ${WRKDIR}/edk2-${GH_TAGNAME}/Build/${PLAT_RESULT_CODE} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME}

	# For sysutils/bhyve-firmware
	${MKDIR} ${STAGEDIR}/${PREFIX}/share/uefi-firmware/
	${RLN} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME} ${STAGEDIR}/${PREFIX}/share/uefi-firmware/${PLAT_FILENAME}
	${RLN} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME_CODE} ${STAGEDIR}/${PREFIX}/share/uefi-firmware/${PLAT_FILENAME_CODE}
	${RLN} ${STAGEDIR}/${PREFIX}/share/${PORTNAME}-${PLAT}/${PLAT_FILENAME_VARS} ${STAGEDIR}/${PREFIX}/share/uefi-firmware/${PLAT_FILENAME_VARS}
.endif

.include <bsd.port.post.mk>
