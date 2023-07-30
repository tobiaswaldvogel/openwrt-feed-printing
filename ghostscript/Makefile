#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ghostscript
PKG_VERSION:=10.01.2
PKG_RELEASE:=3

PKG_MAINTAINER:=Tobias Waldvogel <tobias.waldvogel@gmail.com>
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/ArtifexSoftware/ghostpdl.git
PKG_SOURCE_VERSION:=tags/ghostpdl-$(PKG_VERSION)
PKG_HASH:=722e6461e3b575504068dddc2a6584db15682f01bf54d28109a89fa46f0ae8c1

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/ghostscript
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=ghostscript
  DEPENDS:=+cups +libcupsimage +libfreetype +libtiff +libjpeg +libpng +libexpat +liblcms2 +zlib +fontconfig
  SUBMENU:=Printing
endef

define Package/ghostscript/description
	Ghostscript, an interpreter for the PostScript language and for PDF.
endef

define Package/ghostscript/config
config GS_ENABLE_CONTRIB
	bool "Include contributed device drivers"
	default n

config GS_LARGE_COLOR_INDEX
	bool "Use large color index (16bit instead of 8bit)"
	default n

config GS_EXTRA_DRIVERS
	string "Additional devices drivers (comma separated)"
	default ""
endef

DRIVERS:=pdfwrite,ps2write,cups,pwgraster,appleraster,pclm,pclm8,pdfimage24,pdfimage8,pxlcolor,pxlmono
ifneq ($(CONFIG_GS_ENABLE_CONTRIB),)
  DRIVERS:+=,$(CONFIG_GS_ENABLE_CONTRIB)
endif

CONFIGURE_ARGS += \
	$(if $(CONFIG_GS_ENABLE_CONTRIB),,--disable-contrib) \
	--with-large_color_index=$(if $(CONFIG_GS_LARGE_COLOR_INDEX),1,0) \
	--with-fontpath=/usr/share/fonts \
	--enable-dynamic \
	--with-drivers=$(DRIVERS) \
	--disable-gtk \
	--disable-dbus \
	--disable-hidden-visibility \
	--without-libidn \
	--without-x \
	--without-tesseract \
	--without-versioned-path \
	--enable-fontconfig \
	--with-system-libtiff \
	--with-local-zlib=no \
	--enable-cups \
	--with-pdftoraster \
	--disable-compile-inits \
	--with-cups-serverbin="/usr/lib/cups" \
	--with-cups-serverroot="/etc/cups" \
	--with-cups-datadir="/usr/share/cups"

CONFIGURE_VARS += \
	PKGCONFIG=$(STAGING_DIR_HOST)/bin/pkg-config \
	CUPSCONFIG=$(STAGING_DIR)/usr/bin/cups-config

define Build/Prepare
	$(call Build/Prepare/Default)
	# Remove local copies in order to use the system shared libs
	(cd $(PKG_BUILD_DIR) && $(RM) -r expat ijs jasper lcms2 lcms2mt lcms tesseract tiff jpeg libpng zlib freetype cups/libs)
endef

define Package/ghostscript/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin/
	$(INSTALL_DIR) $(1)/usr/share/ghostscript/lib
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/share/ghostscript/lib/* \
		$(1)/usr/share/ghostscript/lib/
	$(INSTALL_DIR) $(1)/usr/share/ghostscript/iccprofiles
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/iccprofiles/* \
		$(1)/usr/share/ghostscript/iccprofiles/
	$(CP) -r $(PKG_BUILD_DIR)/Resource $(1)/usr/share/ghostscript/
endef

$(eval $(call BuildPackage,ghostscript))
