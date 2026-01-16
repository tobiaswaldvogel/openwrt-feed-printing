#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=poppler
PKG_VERSION:=24.04.0
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=http://poppler.freedesktop.org/
PKG_HASH:=1e804ec565acf7126eb2e9bb3b56422ab2039f7e05863a5dfabdd1ffd1bb77a7

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libpoppler
  SECTION:=libs
  CATEGORY:=Libraries
  SUBMENU:=Printing
  TITLE:=Poppler PDF rendering library
  DEPENDS:=+libpng +libtiff +libjpeg +zlib +liblcms2 +fontconfig +libpthread +libfreetype +libstdcpp
  URL:=http://poppler.freedesktop.org/
endef

define Package/libpoppler/description
	Poppler is a PDF rendering library based on the xpdf-3.0 code base.
endef

define Package/poppler
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Printing
  TITLE:=Poppler PDF rendering library
  DEPENDS:=+libpoppler
  URL:=http://poppler.freedesktop.org/
endef

define Package/poppler/description
	Poppler command line tools
endef

CMAKE_OPTIONS += \
	-DENABLE_BOOST:BOOL=OFF \
	-DENABLE_QT5:BOOL=OFF \
	-DENABLE_QT6:BOOL=OFF \
	-DENABLE_NSS3:BOOL=OFF \
	-DENABLE_GPGME:BOOL=OFF \
	-DENABLE_LIBCURL:BOOL=OFF \
	-DENABLE_GLIB:BOOL=OFF \
	-DENABLE_LIBOPENJPEG:STRING=none \
	-DWITH_Cairo:BOOL=OFF \
	-DWITH_NSS3:BOOL=OFF \
	-DBUILD_CPP_TESTS:BOOL=OFF \
	-DBUILD_GTK_TESTS:BOOL=OFF \
	-DBUILD_QT5_TESTS:BOOL=OFF \
	-DBUILD_QT6_TESTS:BOOL=OFF

define Package/libpoppler/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib*.so* $(1)/usr/lib/
endef

define Package/poppler/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin/
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/cpp $(1)/usr/lib
	$(CP) -r $(PKG_INSTALL_DIR)/usr/include/poppler $(1)/usr/include/
	$(CP) -r $(PKG_BUILD_DIR)/cpp/poppler-version.h $(1)/usr/include/cpp
	$(CP) -r $(PKG_BUILD_DIR)/cpp/poppler-global.h $(1)/usr/include/cpp
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
endef

$(eval $(call BuildPackage,libpoppler))
$(eval $(call BuildPackage,poppler))
