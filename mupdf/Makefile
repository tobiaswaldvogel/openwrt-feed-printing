#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mupdf
PKG_VERSION:=1.20.3-source
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://mupdf.com/downloads/archive/
PKG_HASH:=6b60070f6eec20e8d87d2b5cd22cf49020311a3cf15ee10998e3e5f5f984b1eb
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/mupdf
  SECTION:=utils
  CATEGORY:=Utilities
  SUBMENU:=Printing
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
