#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libcupsfilters
PKG_VERSION:=2.1.1
PKG_RELEASE:=1

PKG_MAINTAINER:=Tobias Waldvogel <tobias.waldvogel@gmail.com>
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OpenPrinting/libcupsfilters.git
PKG_SOURCE_VERSION:=tags/$(PKG_VERSION)
PKG_HASH:=65ea3cddd689b7d6423ef8f73ea589c3b88ed7ccbc5fefd48a344e587d3f7cbc

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libcupsfilters
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=OpenPrinting libcupsfilters
  DEPENDS:=+cups +libcupsimage +fontconfig +libtiff +libjpeg +libpng +libqpdf +CUPS_FILTER_PDF_POPPLER:libpoppler +CUPS_FILTER_PDF_GS:liblcms2 +CUPS_FILTER_PDF_MUPDF:mupdf +CUPS_FILTER_PDF_MUPDF:liblcms2
  URL:=http://www.openprinting.org
  SUBMENU:=Printing
endef

define Package/libcupsfilters/description
	OpenPrinting libcupsfilters
endef

define Package/libcupsfilters/config
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
	 Poppler requires less storage but consumes at lot of memory
	 with big documents.

config CUPS_FILTER_PDF_MUPDF
	bool "MuPDF: mupdftoraster"

endchoice
endef

#EXTRA_CFLAGS+= \
#	-std=c++17 \
#	-DHAVE_CPP_POPPLER_VERSION_H \
#	-DPOINTERHOLDER_TRANSITION=0 \
#	-Wno-deprecated-declarations

EXTRA_CFLAGS+= \
	-Wno-maybe-uninitialized \
	-Wno-unused-function

CONFIGURE_ARGS += \
	--disable-dbus \
	--disable-exif \
	--enable-imagefilters \
	--enable-werror \
	--with-ippfind-path=/usr/bin/ippfind \
	--$(if $(CONFIG_CUPS_FILTER_PDF_GS),enable,disable)-ghostscript \
	$(if $(CONFIG_CUPS_FILTER_PDF_GS),--with-gs-path=/usr/bin/gs,) \
	$(if $(CONFIG_CUPS_FILTER_PDF_GS),--with-pdftops-path=/usr/bin/gs,) \
	--with-pdftops=$(if $(CONFIG_CUPS_FILTER_PDF_GS),gs,pdftops) \
	--$(if $(CONFIG_CUPS_FILTER_PDF_POPPLER),enable,disable)-poppler \
	--$(if $(CONFIG_CUPS_FILTER_PDF_MUPDF),enable,disable)-mutool \
	$(if $(CONFIG_CUPS_FILTER_PDF_MUPDF),--with-mutool-path=/usr/bin/mutool,)


define Package/libcupsfilters/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/usr/lib/
	$(call InstallDir,DATA,$(1),/usr/share/cups/charsets,*)
	$(call InstallDir,DATA,$(1),/usr/share/cups/data,*test*)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libcupsfilters))
