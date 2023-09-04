#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk

PKG_NAME:=cups
PKG_VERSION:=2.4.6
PKG_RELEASE:=2

PKG_MAINTAINER:=Tobias Waldvogel <tobias.waldvogel@gmail.com>
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OpenPrinting/cups.git
PKG_SOURCE_VERSION:=tags/v$(PKG_VERSION)
PKG_HASH:=1a61eeaa660861f8519174ee07f0d636c5a88026cc6773f0c162b33fefa9d1be
PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=LICENSE.txt

PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/cups/Default
  URL:=http://www.cups.org/
  SUBMENU:=Printing
endef

define Package/cups
$(call Package/cups/Default)
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=+libcups +libusb-1.0 +libstdcpp +libubox +libubus +umdns
  TITLE:=Common UNIX Printing System (daemon)
endef

define Package/cups/description
	Common UNIX Printing System (daemon)
endef

define Package/cups/conffiles
/etc/cups/classes.conf
/etc/cups/cupsd.conf
/etc/cups/printers.conf
endef

define Package/cups-bsd
$(call Package/cups/Default)
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libcups
  TITLE:=Common UNIX Printing System - BSD commands (old)
endef

define Package/cups-bsd/description
	Common UNIX Printing System - BSD commands (old)
endef

define Package/cups-client
$(call Package/cups/Default)
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libcups +libcupsimage
  TITLE:=Common UNIX Printing System - Client commands
endef

define Package/cups-client/conffiles
/etc/cups/client.conf
endef

define Package/cups-client/description
	Common UNIX Printing System - Client commands
endef

define Package/libcups
$(call Package/cups/Default)
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=+zlib +libpthread +libpng +libjpeg +libubox +libubus
  TITLE:=Common UNIX Printing System - Core library
endef

define Package/libcups/description
	Common UNIX Printing System - Core library
endef

define Package/libcupsimage
$(call Package/cups/Default)
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=+libcups
  TITLE:=Common UNIX Printing System - Image library
endef

define Package/libcupsimage/description
	Common UNIX Printing System - Image library
endef

CONFIGURE_ARGS += \
		--libdir=/usr/lib \
		--with-languages= \
		--with-cups-user="nobody" \
		--with-cups-group="nogroup" \
		--with-system-groups="root" \
		--enable-default-shared \
		--enable-shared \
		--enable-libusb \
		--disable-dbus \
		--with-dnssd=no \
		--with-tls=no \
		--disable-acl \
		--disable-pam \
		--disable-gssapi \
		--without-perl \
		--without-python

CONFIGURE_VARS += \
		UNAME="Linux" \
		LIBS="$(TARGET_LDFLAGS) -lz -lpng -ljpeg -lubus -lubox"

MAKE_VARS += \
		STRIPPROG="/bin/true" \
		CHMODPROG="/bin/true" \
		CHGRPPROG="/bin/true" \
		CHOWNPROG="/bin/true"

EXTRA_CFLAGS+=-Wno-sign-conversion -DHAVE_UBUS
TARGET_LDFLAGS+=-Wl,-rpath-link=$(STAGING_DIR)/usr/lib

define InstallDir
	$(INSTALL_DIR) $(2)$(3)
	$(INSTALL_$(1)) \
		$(foreach pat,$(4),$(if $(5),$(5),$(PKG_INSTALL_DIR))$(3)/$(pat)) \
		$(2)$(3)/
endef

define InstallDirLib
	$(INSTALL_DIR) $(1)$(2)
	$(CP) $(PKG_INSTALL_DIR)$(2)/$(3) $(1)$(2)/
endef

define InstallLink
	$(foreach pat,$(3),$(LN) $(2) $(1)/$(pat); )
endef

define Package/cups/install
	$(call InstallDir,DATA,$(1),/etc/cups,*.conf*)
	$(INSTALL_DATA) ./files/etc/cups/* $(1)/etc/cups/
	$(LN) /tmp/cups $(1)/etc/cups/certs

	$(call InstallDir,BIN,$(1),/usr/sbin,cupsctl cupsd)

	$(call InstallDir,BIN,$(1),/usr/lib/cups/backend,*)
	$(call InstallDir,BIN,$(1),/usr/lib/cups/command,*)
	$(call InstallDir,BIN,$(1),/usr/lib/cups/cgi-bin,*)
	$(call InstallDir,BIN,$(1),/usr/lib/cups/daemon,*)
	$(call InstallDir,BIN,$(1),/usr/lib/cups/monitor,*)
	$(call InstallDir,BIN,$(1),/usr/lib/cups/filter,*)
	# needed for cups to find usb printers per http://wiki.openwrt.org/doc/howto/cups.server
	chmod 700 $(1)/usr/lib/cups/backend/usb

	$(INSTALL_DIR) $(1)/usr/share/cups/banners
	# Web interface
	$(call InstallDir,DATA,$(1),/usr/share/cups/templates,*.tmpl)
	$(call InstallDir,DATA,$(1),/usr/share/cups/mime,*)
	$(call InstallDir,DATA,$(1),/usr/share/doc/cups,*.html *.css *.txt)
	$(call InstallDir,DATA,$(1),/usr/share/doc/cups/images,*)
	# Init file
	$(call InstallDir,BIN,$(1),/etc/init.d,cupsd,files)
endef

define Package/cups-bsd/install
	$(call InstallDir,BIN,$(1),/usr/bin,lprm lpq lpr)
	$(call InstallDir,BIN,$(1),/usr/sbin,lpc)
endef

define Package/cups-client/install
	$(call InstallDir,BIN,$(1),/usr/bin,lp cancel cupstestppd ipptool lpoptions lpstat)
	$(call InstallDir,BIN,$(1),/usr/sbin,cupsaccept cupsfilter lpadmin lpinfo lpmove)
	$(call InstallLink,$(1)/usr/sbin,cupsaccept,accept cupsenable,cupsdisable,reject,cupsreject)
	$(call InstallDir,DATA,$(1),/usr/share/cups/ipptool,*.test)
endef

define Package/libcups/install
	$(call InstallDir,BIN,$(1),/usr/lib,libcups.so.2)
	$(call InstallLink,$(1)/usr/lib,libcups.so.2,libcups.so)
endef

define Package/libcupsimage/install
	$(call InstallDir,BIN,$(1),/usr/lib,libcupsimage.so.2)
	$(call InstallLink,$(1)/usr/lib,libcupsimage.so.2,libcupsimage.so)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(2)/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/cups-config $(2)/bin/
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/cups $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib*/libcups*.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,cups))
$(eval $(call BuildPackage,libcups))
$(eval $(call BuildPackage,libcupsimage))
$(eval $(call BuildPackage,cups-bsd))
$(eval $(call BuildPackage,cups-client))
