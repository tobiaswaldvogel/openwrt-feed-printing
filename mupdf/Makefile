#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mupdf
PKG_VERSION:=1.24.1-source
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://mupdf.com/downloads/archive/
PKG_HASH:=5840308280a2be7bd55f5e8a0b5a3ab8839689fa389a48a91433dcabd465be4d
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/mupdf
  SECTION:=utils
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+libopenssl
  TITLE:=MuPDF is a lightweight PDF, XPS, and E-book viewer.
  URL:=http://www.mupdf.com
endef

define Package/mupdf/description
	MuPDF command line tools
endef

MAKE_FLAGS += HAVE_X11=no HAVE_GLUT=no

define Package/mupdf/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/local/bin/mutool $(1)/usr/bin/
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/$(PKG_NAME) $(1)/usr/lib
	$(CP) -r $(PKG_INSTALL_DIR)/usr/local/include/$(PKG_NAME) $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/local/lib/* $(1)/usr/lib
endef

$(eval $(call BuildPackage,mupdf))
