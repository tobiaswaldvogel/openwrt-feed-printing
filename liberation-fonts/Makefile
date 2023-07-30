#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=liberation-fonts-ttf
PKG_VERSION:=2.1.5
PKG_RELEASE:=1
PKG_LICENSE:=GPL-3.0
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/liberationfonts/liberation-fonts/files/7261482
PKG_MD5SUM:=7191c669bf38899f73a2094ed00f7b800553364f90e2637010a69c0e268f25d0


#https://github.com/liberationfonts/liberation-fonts/files/7261482/liberation-fonts-ttf-2.1.5.tar.gz

include $(INCLUDE_DIR)/package.mk

define Package/liberation-fonts
  SECTION:=fonts
  CATEGORY:=Fonts
  TITLE:=liberation-fonts
endef

define Package/liberation-fonts/description
The Liberation(tm) Fonts is a font family which aims at metric compatibility
with Arial, Times New Roman, and Courier New. It is sponsored by Red Hat
endef

define Build/Configure
endef

define Build/Compile
endef

define FontPackage
  define Package/$(PKG_NAME)-$(1)
    SECTION:=fonts
    CATEGORY:=Fonts
    SUBMENU:=Liberation(tm) Fonts
    TITLE:=$(2)
  endef

  define Package/$(PKG_NAME)-$(1)/install
		$(INSTALL_DIR) $$(1)/usr/share/fonts/truetype/liberation
		$(INSTALL_DATA) $(PKG_BUILD_DIR)/$2 \
			$$(1)/usr/share/fonts/truetype/liberation/
  endef

  define Package/$(PKG_NAME)-$(1)/postinst
#!/bin/sh
[ -z "$$$${IPKG_INSTROOT}" -a -f /usr/bin/fc-cache ] && /usr/bin/fc-cache --force --verbose || exit 0
  endef

  $$(eval $$(call BuildPackage,$(PKG_NAME)-$(1)))
endef

$(eval $(call FontPackage,LiberationMono-Bold,LiberationMono-Bold.ttf))
$(eval $(call FontPackage,LiberationMono-BoldItalic,LiberationMono-BoldItalic.ttf))
$(eval $(call FontPackage,LiberationMono-Italic,LiberationMono-Italic.ttf))
$(eval $(call FontPackage,LiberationMono,LiberationMono-Regular.ttf))
$(eval $(call FontPackage,LiberationSans-Bold,LiberationSans-Bold.ttf))
$(eval $(call FontPackage,LiberationSans-BoldItalic,LiberationSans-BoldItalic.ttf))
$(eval $(call FontPackage,LiberationSans-Italic,LiberationSans-Italic.ttf))
$(eval $(call FontPackage,LiberationSans,LiberationSans-Regular.ttf))
$(eval $(call FontPackage,LiberationSerif-Bold,LiberationSerif-Bold.ttf))
$(eval $(call FontPackage,LiberationSerif-BoldItalic,LiberationSerif-BoldItalic.ttf))
$(eval $(call FontPackage,LiberationSerif-Italic,LiberationSerif-Italic.ttf))
$(eval $(call FontPackage,LiberationSerif,LiberationSerif-Regular.ttf))
