#
# Copyright (C) 2007-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=brlaser
PKG_VERSION=1.0
PKG_RELEASE=1
PKG_SOURCE_PROTO=git
PKG_SOURCE_URL=https://github.com/pdewacht/brlaser.git
PKG_SOURCE_VERSION=9d7ddda8383bfc4d205b5e1b49de2b8bcd9137f1
PKG_HASH=f2d89b63fe1955cc365f8122023b6b3d4758d5bb20e55a72788212cb6951710f

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/$(PKG_NAME)
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Printing
  DEPENDS:=+libcupsimage +libstdcpp
  TITLE:=$(PKG_NAME)
  URL:=https://github.com/
endef

define Package/$(PKG_NAME)/description
  $(PKG_NAME)
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib/cups/filter
	$(INSTALL_BIN) \
		$(PKG_INSTALL_DIR)/usr/lib/cups/filter/rastertobrlaser \
		$(1)/usr/lib/cups/filter
#	$(INSTALL_DIR) $(1)/usr/share/ppd
#	$(INSTALL_DATA) ./files/hl3040cn.ppd $(1)/usr/share/ppd/
endef


$(eval $(call BuildPackage,$(PKG_NAME)))
