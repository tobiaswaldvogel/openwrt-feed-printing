#
# Copyright (C) 2007-2010 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=brhl3040cnfilter
PKG_VERSION=1.0
PKG_RELEASE=1
PKG_SOURCE:=hl3040cnlpr-1.1.2-1.i386.deb
PKG_SOURCE_URL:=http://download.brother.com/welcome/dlf005905
PKG_HASH:=ea5f589085fe7c99e655b9088f5933e5

include $(INCLUDE_DIR)/package.mk
RSTRIP:=true

define Package/$(PKG_NAME)
  SECTION:=net
  CATEGORY:=Network
  SUBMENU:=Printing
ifeq ($(ARCH),aarch64)
  DEPENDS:=+box86 +libarmeabi
endif
  TITLE:=Brother HL3040CN x86 binary filter
  URL:=https://github.com/
endef

define Package/$(PKG_NAME)/description
  Brother HL3040CN x86 binary filter
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	( cd $(PKG_BUILD_DIR); \
		$(TARGET_AR) -p $(DL_DIR)/$(PKG_SOURCE) data.tar.gz | tar -xzf - \
	)
endef

define Build/Configure
endef

define Build/Compile
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/opt/brother/Printers/hl3040cn/inf/lut
	$(INSTALL_DATA) \
		$(PKG_BUILD_DIR)/opt/brother/Printers/hl3040cn/inf/lut/* \
		$(1)/opt/brother/Printers/hl3040cn/inf/lut/
	$(INSTALL_BIN) \
		$(PKG_BUILD_DIR)/opt/brother/Printers/hl3040cn/lpd/brhl3040cnfilter \
		$(1)/opt/brother/Printers/hl3040cn/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
