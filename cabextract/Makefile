#
# Copyright (C) 2007-2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=cabextract
PKG_VERSION:=1.9.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://www.cabextract.org.uk
PKG_HASH:=afc253673c8ef316b4d5c29cc4aa8445844bee14afffbe092ee9469405851ca7

PKG_MAINTAINER:=Tobias Waldvogel <tobias.waldvogel@gmail.com>

include $(INCLUDE_DIR)/host-build.mk
include $(INCLUDE_DIR)/package.mk

define Package/cabextract
  SUBMENU:=Compression
  URL:=https://www.cabextract.org.uk
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libbz2
  TITLE:=cabextract is a compression utility.
endef

define Package/cabextract/description
	cabextract is Free Software for extracting Microsoft cabinet filesc
endef


define Package/cabextract/install
	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/cabextract $(1)/usr/bin/cabextract
endef

define Host/Install
	$(INSTALL_DIR) $(STAGING_DIR_HOSTPKG)/bin/
	$(MAKE) -C $(HOST_BUILD_DIR) PREFIX=$(STAGING_DIR_HOSTPKG)/ install
endef

$(eval $(call BuildPackage,cabextract))
$(eval $(call HostBuild))
