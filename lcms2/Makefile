#
# Copyright (C) 2007-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=lcms2
PKG_VERSION:=2.16
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@SF/lcms
PKG_HASH:=d873d34ad8b9b4cea010631f1a6228d2087475e4dc5e763eb81acc23d9d45a51

PKG_INSTALL:=1

define Package/liblcms2
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=Little CMS color engine
  DEPENDS:=+libtiff +libjpeg +zlib
  URL:=http://www.littlecms.com/
  SUBMENU:=Printing
endef

define Package/lcms2/description
	Little CMS color engine library
endef

include $(INCLUDE_DIR)/package.mk

define Package/lcms2
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Little CMS color engine
  DEPENDS:=+libtiff +libjpeg +zlib
  URL:=http://www.littlecms.com/
  SUBMENU:=Printing
endef

define Package/lcms2/description
	Little CMS color engine
endef

define Package/lcms2/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/usr/bin/
endef

define Package/liblcms2/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/lib*.so* $(1)/usr/lib/
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
endef

$(eval $(call BuildPackage,liblcms2))
$(eval $(call BuildPackage,lcms2))
