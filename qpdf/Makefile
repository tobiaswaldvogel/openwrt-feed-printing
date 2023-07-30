#
# Copyright (C) 2007-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qpdf
PKG_VERSION:=11.5.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@SF/$(PKG_NAME)
PKG_HASH:=15cb419e72c494a4a4b2e7c0eb9f4e980c8fd4e61ccdea64399e987f4c56c8ee

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libqpdf
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=PDF transformation library
  DEPENDS:= +libpcre +zlib +libstdcpp +libjpeg +libopenssl +libatomic
  URL:=http://qpdf.sourceforge.net/
endef

define Package/libqpdf/description
PDF transformation library
endef

define Package/qpdf
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=QPDF is a command-line program for transformations on PDF files.
  DEPENDS:= +libqpdf
  URL:=http://qpdf.sourceforge.net/
  SUBMENU:=Printing
endef

define Package/qpdf/description
QPDF is a command-line program that does structural, content-preserving
transformations on PDF files. It could have been called something like pdf-to-pdf.
It also provides  many useful capabilities to developers of PDF-producing software
or for people who just want to look at the innards of a PDF file to learn more
about how they work.
endef

CMAKE_INSTALL:=1
CMAKE_BINARY_SUBDIR:=build

CMAKE_OPTIONS += \
	-DUSE_IMPLICIT_CRYPTO:BOOL=OFF \
	-DREQUIRE_CRYPTO_OPENSSL:BOOL=ON \
	-DRANDOM_DEVICE:FILEPATH=/dev/urandom

define Package/libqpdf/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib*.so* $(1)/usr/lib/
endef

define Package/qpdf/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin/
endef

define Build/InstallDev
	$(call Build/InstallDev/cmake,$(1))
	$(SED) 's,/usr/include,$$$${prefix}/include,g' $(1)/usr/lib/pkgconfig/libqpdf.pc
	$(SED) 's,/usr/lib,$$$${prefix}/lib,g' $(1)/usr/lib/pkgconfig/libqpdf.pc
endef

$(eval $(call BuildPackage,libqpdf))
$(eval $(call BuildPackage,qpdf))
