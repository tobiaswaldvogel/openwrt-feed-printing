#
# Copyright (C) 2007-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=brhl3040cncupswrapper
PKG_VERSION=1.0
PKG_RELEASE=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Printing
  DEPENDS:=+libcupsimage +brhl3040cnfilter
  TITLE:=$(PKG_NAME)
  URL:=https://github.com/
endef

define Package/$(PKG_NAME)/description
  $(PKG_NAME)
endef

define Build/Configure
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib/cups/filter
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/usr/lib/cups/filter
	$(INSTALL_DIR) $(1)/usr/share/ppd
	$(INSTALL_DATA) ./files/hl3040cn.ppd $(1)/usr/share/ppd/
endef


$(eval $(call BuildPackage,$(PKG_NAME)))
