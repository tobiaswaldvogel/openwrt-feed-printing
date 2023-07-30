#
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=msttcorefonts
PKG_VERSION:=1.0
PKG_RELEASE:=1
PKG_BUILD_DEPENDS:=cabextract/host
PKG_MAINTAINER:=Tobias Waldvogel <tobias.waldvogel@gmail.com>

include $(INCLUDE_DIR)/package.mk

FONT_DOWNLOAD_URL=@SF/corefonts/the%20fonts/final/

define Download/andale32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=andale32.exe
  HASH:=cbdc2fdd7d2ed0832795e86a8b9ee19a
endef
$(eval $(call Download,andale32.exe))

define Download/arial32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=arial32.exe
  HASH:=9637df0e91703179f0723ec095a36cb5
endef
$(eval $(call Download,arial32.exe))

define Download/arialb32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=arialb32.exe
  HASH:=c9089ae0c3b3d0d8c4b0a95979bb9ff0
endef
$(eval $(call Download,arialb32.exe))

define Download/comic32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=comic32.exe
  HASH:=2b30de40bb5e803a0452c7715fc835d1
endef
$(eval $(call Download,comic32.exe))

define Download/courie32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=courie32.exe
  HASH:=4e412c772294403ab62fb2d247d85c60
endef
$(eval $(call Download,courie32.exe))

define Download/georgi32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=georgi32.exe
  HASH:=4d90016026e2da447593b41a8d8fa8bd
endef
$(eval $(call Download,georgi32.exe))

define Download/impact32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=impact32.exe
  HASH:=7907c7dd6684e9bade91cff82683d9d7
endef
$(eval $(call Download,impact32.exe))

define Download/times32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=times32.exe
  HASH:=ed39c8ef91b9fb80f76f702568291bd5
endef
$(eval $(call Download,times32.exe))

define Download/trebuc32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=trebuc32.exe
  HASH:=0d7ea16cac6261f8513a061fbfcdb2b5
endef
$(eval $(call Download,trebuc32.exe))

define Download/webdin32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=webdin32.exe
  HASH:=230a1d13a365b22815f502eb24d9149b
endef
$(eval $(call Download,webdin32.exe))

define Download/verdan32.exe
  URL:=$(FONT_DOWNLOAD_URL)
  FILE:=verdan32.exe
  HASH:=12d2a75f8156e10607be1eaa8e8ef120
endef
$(eval $(call Download,verdan32.exe))

CABEXTRACT:=$(STAGING_DIR_HOSTPKG)/bin/cabextract

define Build/Configure
endef

define Build/Compile/Extract
	$(CABEXTRACT) -d $(PKG_BUILD_DIR) -F *.TTF $(DL_DIR)/$132.exe
endef

define Build/Compile
	$(call Build/Compile/Extract,andale)
	$(call Build/Compile/Extract,arial)
	$(call Build/Compile/Extract,arialb)
	$(call Build/Compile/Extract,comic)
	$(call Build/Compile/Extract,courie)
	$(call Build/Compile/Extract,georgi)
	$(call Build/Compile/Extract,impact)
	$(call Build/Compile/Extract,times)
	$(call Build/Compile/Extract,trebuc)
	$(call Build/Compile/Extract,webdin)
	$(call Build/Compile/Extract,verdan)
endef

define FontPackage
  define Package/$(PKG_NAME)-$(1)
    SECTION:=fonts
    CATEGORY:=Fonts
    SUBMENU:=Microsoft core fonts
    TITLE:=$(2)
  endef

  define Package/$(PKG_NAME)-$(1)/install
		$(INSTALL_DIR) $$(1)/usr/share/fonts/truetype/$(PKG_NAME)
		$(INSTALL_DATA) $(PKG_BUILD_DIR)/$2 \
			$$(1)/usr/share/fonts/truetype/$(PKG_NAME)/
  endef

  define Package/$(PKG_NAME)-$(1)/postinst
#!/bin/sh
[ -z "$$$${IPKG_INSTROOT}" -a -f /usr/bin/fc-cache ] && /usr/bin/fc-cache --force --verbose || exit 0
  endef

  $$(eval $$(call BuildPackage,$(PKG_NAME)-$(1)))
endef

$(eval $(call FontPackage,AndaleMono,AndaleMo.TTF))
$(eval $(call FontPackage,ArialMT,Arial.TTF))
$(eval $(call FontPackage,Arial-BoldMT,Arialbd.TTF))
$(eval $(call FontPackage,Arial-BoldItalicMT,Arialbi.TTF))
$(eval $(call FontPackage,Arial-ItalicMT,Ariali.TTF))
$(eval $(call FontPackage,Arial-Black,AriBlk.TTF))
$(eval $(call FontPackage,ComicSansMS,Comic.TTF))
$(eval $(call FontPackage,ComicSansMS-Bold,Comicbd.TTF))
$(eval $(call FontPackage,CourierNewPSMT,cour.ttf))
$(eval $(call FontPackage,CourierNewPS-BoldMT,courbd.ttf))
$(eval $(call FontPackage,CourierNewPS-BoldItalicMT,courbi.ttf))
$(eval $(call FontPackage,CourierNewPS-ItalicMT,couri.ttf))
$(eval $(call FontPackage,Georgia,Georgia.TTF))
$(eval $(call FontPackage,Georgia-Bold,Georgiab.TTF))
$(eval $(call FontPackage,Georgia-Italic,Georgiai.TTF))
$(eval $(call FontPackage,Georgia-BoldItalic,Georgiaz.TTF))
$(eval $(call FontPackage,Impact,Impact.TTF))
$(eval $(call FontPackage,TimesNewRomanPSMT,Times.TTF))
$(eval $(call FontPackage,TimesNewRomanPS-BoldMT,Timesbd.TTF))
$(eval $(call FontPackage,TimesNewRomanPS-BoldItalicMT,Timesbi.TTF))
$(eval $(call FontPackage,TimesNewRomanPS-ItalicMT,Timesi.TTF))
$(eval $(call FontPackage,TrebuchetMS,trebuc.ttf))
$(eval $(call FontPackage,TrebuchetMS-Bold,Trebucbd.ttf))
$(eval $(call FontPackage,Trebuchet-BoldItalic,trebucbi.ttf))
$(eval $(call FontPackage,TrebuchetMS-Italic,trebucit.ttf))
$(eval $(call FontPackage,Verdana,Verdana.TTF))
$(eval $(call FontPackage,Verdana-Bold,Verdanab.TTF))
$(eval $(call FontPackage,Verdana-Italic,Verdanai.TTF))
$(eval $(call FontPackage,Verdana-BoldItalic,Verdanaz.TTF))
$(eval $(call FontPackage,Webdings,Webdings.TTF))
