/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2019 Intel Corporation
 */

#ifndef __INTEL_SPRITE_H__
#define __INTEL_SPRITE_H__

#include <linux/types.h>

struct drm_device;
struct drm_file;
#if IS_ENABLED(CPTCFG_DRM_I915_DISPLAY)
#include "intel_display.h"

struct drm_display_mode;
struct drm_i915_private;
struct intel_crtc_state;
struct intel_plane_state;

/*
 * FIXME: We should instead only take spinlocks once for the entire update
 * instead of once per mmio.
 */
#if IS_ENABLED(CONFIG_PROVE_LOCKING)
#define VBLANK_EVASION_TIME_US 250
#else
#define VBLANK_EVASION_TIME_US 100
#endif

struct intel_plane *intel_sprite_plane_create(struct drm_i915_private *dev_priv,
					      enum pipe pipe, int plane);
int intel_sprite_set_colorkey_ioctl(struct drm_device *dev, void *data,
				    struct drm_file *file_priv);
int intel_plane_check_src_coordinates(struct intel_plane_state *plane_state);
int chv_plane_check_rotation(const struct intel_plane_state *plane_state);

static inline u8 icl_hdr_plane_mask(void)
{
	return BIT(PLANE_PRIMARY) |
		BIT(PLANE_SPRITE0) | BIT(PLANE_SPRITE1);
}

int ivb_plane_min_cdclk(const struct intel_crtc_state *crtc_state,
			const struct intel_plane_state *plane_state);
int hsw_plane_min_cdclk(const struct intel_crtc_state *crtc_state,
			const struct intel_plane_state *plane_state);
#else
static inline int intel_sprite_set_colorkey_ioctl(struct drm_device *dev, void *data,
				    struct drm_file *file_priv) { return 0; }
#endif /* CPTCFG_DRM_I915_DISPLAY */

#endif /* __INTEL_SPRITE_H__ */