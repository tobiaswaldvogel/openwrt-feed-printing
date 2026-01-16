#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=openprinting-cups-filters
PKG_VERSION:=2.0.1
PKG_RELEASE:=4

PKG_MAINTAINER:=Tobias Waldvogel <tobias.waldvogel@gmail.com>
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OpenPrinting/cups-filters.git
PKG_SOURCE_VERSION:=tags/$(PKG_VERSION)
PKG_HASH:=d1347e36053356fd949fb8ec8f3563e9af24690d23906fc7034dcf6165fe6c47

PKG_FIXUP:=autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/openprinting-cups-filters
  SECTION:=net
  CATEGORY:=Network
  TITLE:=OpenPrinting CUPS filters
  DEPENDS:=+libcupsfilters +libppd
  URL:=http://www.openprinting.org
  SUBMENU:=Printing
endef
 
define Package/openprinting-cups-filters/description
	CUPS filters maintained by OpenPrinting.
	The CUPS Filters package contains backends, filters and other software that was once part of the core CUPS distribution but is no longer maintained by Apple Inc.
endef

EXTRA_CFLAGS+= \
	-std=gnu17 \
	-DHAVE_CPP_POPPLER_VERSION_H \
	-DPOINTERHOLDER_TRANSITION=0 \
	-Wno-deprecated-declarations \
	-Wno-incompatible-pointer-types

CONFIGURE_ARGS += \
	--disable-avahi \
	--disable-rpath \
	--enable-werror \
	--with-shell=/bin/sh \
	--$(if $(CONFIG_PACKAGE_ghostscript),enable,disable)-ghostscript \
	$(if $(CONFIG_PACKAGE_ghostscript),--with-gs-path=/usr/bin/gs,) \
	--$(if $(CONFIG_PACKAGE_libpoppler),enable,disable)-poppler \
	--$(if $(CONFIG_PACKAGE_mupdf),enable,disable)-mutool \
	$(if $(CONFIG_PACKAGE_mupdf),--with-mutool-path=/usr/bin/mutool,)


define InstallDir
	$(INSTALL_DIR) $(2)$(3)
	$(INSTALL_$(1)) \
		$(foreach pat,$(4),$(if $(5),$(5),$(PKG_INSTALL_DIR))$(3)/$(pat)) \
		$(2)$(3)/
endef

define Package/openprinting-cups-filters/install
	$(call InstallDir,BIN,$(1),/usr/lib/cups/filter,*)
	$(call InstallDir,DATA,$(1),/usr/share/cups/mime,*)
	$(call InstallDir,DATA,$(1),/usr/share/ppdc,*)
	$(call InstallDir,DATA,$(1),/usr/share/ppd/cupsfilters,*)
endef

define Package/postinst
#!/bin/sh
[ -z "$$$${IPKG_INSTROOT}" ] && /etc/init.d/cupsd restart
endef

$(eval $(call BuildPackage,openprinting-cups-filters))
