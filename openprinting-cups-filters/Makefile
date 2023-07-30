#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=openprinting-cups-filters
PKG_VERSION:=1.28.17
PKG_RELEASE:=3

PKG_MAINTAINER:=Tobias Waldvogel <tobias.waldvogel@gmail.com>
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OpenPrinting/cups-filters.git
PKG_SOURCE_VERSION:=tags/$(PKG_VERSION)
PKG_HASH:=eb9214ab144eec009e4bb6533ffdfd52c5ac029b3cc1d93d58e1879e7a9a7ae9

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/openprinting-cups-filters
  SECTION:=net
  CATEGORY:=Network
  TITLE:=OpenPrinting CUPS filters
  DEPENDS:=+cups +libcupsimage +fontconfig +libtiff +libjpeg +libpng +libqpdf +CUPS_FILTER_PDF_POPPLER:libpoppler +CUPS_FILTER_PDF_GS:liblcms2 +CUPS_FILTER_PDF_MUPDF:mupdf +CUPS_FILTER_PDF_MUPDF:liblcms2
  URL:=http://www.openprinting.org
  SUBMENU:=Printing
endef

define Package/openprinting-cups-filters/config
choice CUPS_FILTER_PDF_BACKEND
	depends on PACKAGE_openprinting-cups-filters
	bool "PDF backend for raster conversion"
	default CUPS_FILTER_PDF_GS

config CUPS_FILTER_PDF_GS
	bool "Ghostscript: gstoraster"
	help
	 Ghostscript requires more storage but much less memory than poppler.

config CUPS_FILTER_PDF_POPPLER
	bool "Poppler: pdftoraster"
	help
	 Popper requires less storage but consumes at lot of memory
	 with big documents.

config CUPS_FILTER_PDF_MUPDF
	bool "MuPDF: mupdftoraster"

endchoice
endef

define Package/openprinting-cups-filters/description
	CUPS filters maintained by OpenPrinting.
	The CUPS Filters package contains backends, filters and other software that was once part of the core CUPS distribution but is no longer maintained by Apple Inc.
endef

EXTRA_CFLAGS+= \
	-std=c++17 \
	-DHAVE_CPP_POPPLER_VERSION_H \
	-DPOINTERHOLDER_TRANSITION=0 \
	-Wno-deprecated-declarations

CONFIGURE_ARGS += \
	--disable-dbus \
	--disable-avahi \
	--disable-exif \
	--disable-ldap \
	--disable-braille \
	--enable-imagefilters \
	--$(if $(CONFIG_CUPS_FILTER_PDF_GS),enable,disable)-ghostscript \
	$(if $(CONFIG_CUPS_FILTER_PDF_GS),--with-gs-path=/usr/bin/gs,) \
	$(if $(CONFIG_CUPS_FILTER_PDF_GS),--with-pdftops-path=/usr/bin/gs,) \
	--with-pdftops=$(if $(CONFIG_CUPS_FILTER_PDF_GS),gs,pdftops) \
	--$(if $(CONFIG_CUPS_FILTER_PDF_POPPLER),enable,disable)-poppler \
	--$(if $(CONFIG_CUPS_FILTER_PDF_MUPDF),enable,disable)-mutool \
	$(if $(CONFIG_CUPS_FILTER_PDF_MUPDF),--with-mutool-path=/usr/bin/mutool,)

define InstallDir
	$(INSTALL_DIR) $(2)$(3)
	$(INSTALL_$(1)) \
		$(foreach pat,$(4),$(if $(5),$(5),$(PKG_INSTALL_DIR))$(3)/$(pat)) \
		$(2)$(3)/
endef

define InstallDirLib
	$(INSTALL_DIR) $(1)$(2)
	$(CP) $(PKG_INSTALL_DIR)$(2)/$(3) $(1)$(2)/
endef

define InstallLink
	$(foreach pat,$(3),$(LN) $(2) $(1)/$(pat); )
endef

define Package/openprinting-cups-filters/install
	$(call InstallDir,BIN,$(1),/usr/lib,libcupsfilters.so.1.0.0 libfontembed.so.1.0.0,)
	$(call InstallLink,$(1)/usr/lib,libcupsfilters.so.1.0.0,libcupsfilters.so.1 libcupsfilters.so)
	$(call InstallLink,$(1)/usr/lib,libfontembed.so.1.0.0,libfontembed.so.1 libfontembed.so)

	$(call InstallDir,BIN,$(1),/usr/lib/cups/filter,*)
	$(call InstallDir,DATA,$(1),/usr/share/cups/charsets,*)
	$(call InstallDir,DATA,$(1),/usr/share/cups/mime,*)
	$(call InstallDir,DATA,$(1),/usr/share/cups/ppdc,*)
	$(call InstallDir,DATA,$(1),/usr/share/cups/data,*test*)
	$(call InstallDir,DATA,$(1),/usr/share/ppd/cupsfilters,*)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib/
endef

define Package/postinst
#!/bin/sh
[ -z "$$$${IPKG_INSTROOT}" ] && /etc/init.d/cupsd restart
endef

$(eval $(call BuildPackage,openprinting-cups-filters))
