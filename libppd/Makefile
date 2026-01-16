#
# Copyright (C) 2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libppd
PKG_VERSION:=2.0.0
PKG_RELEASE:=1

PKG_MAINTAINER:=Tobias Waldvogel <tobias.waldvogel@gmail.com>
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OpenPrinting/libppd.git
PKG_SOURCE_VERSION:=tags/$(PKG_VERSION)
PKG_HASH:=ff569dc9c4d0d15aa2779fe196dba6175a5d99b0f17c61c1c2abe3f7805c1924

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/libppd
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=OpenPrinting libppd
  DEPENDS:=+libcupsfilters
  SUBMENU:=Printing
endef

define Package/libppd/description
	OpenPrinting libppd
endef

CONFIGURE_ARGS += \
	--disable-dbus \
	--disable-acroread \
	--disable-pdftocairo \
	--enable-werror \
	--$(if $(CONFIG_PACKAGE_ghostscript),enable,disable)-ghostscript \
	$(if $(CONFIG_PACKAGE_ghostscript),--with-gs-path=/usr/bin/gs,) \
	$(if $(CONFIG_PACKAGE_ghostscript),--with-pdftops-path=/usr/bin/gs,) \
	--with-pdftops=$(if $(CONFIG_PACKAGE_ghostscript),gs,pdftops) \
	--$(if $(CONFIG_PACKAGE_libpoppler),enable,disable)-pdftops \
	--$(if $(CONFIG_PACKAGE_mupdf),enable,disable)-mutool \
	$(if $(CONFIG_PACKAGE_mupdf),--with-mutool-path=/usr/bin/mutool,)


define InstallDir
	$(INSTALL_DIR) $(2)$(3)
	$(INSTALL_$(1)) \
		$(foreach pat,$(4),$(if $(5),$(5),$(PKG_INSTALL_DIR))$(3)/$(pat)) \
		$(2)$(3)/
endef

define Package/libppd/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/usr/lib
	$(call InstallDir,DATA,$(1),/usr/share/ppdc,*)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,libppd))
