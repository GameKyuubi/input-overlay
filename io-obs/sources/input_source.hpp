/**
 * This file is part of input-overlay
 * which is licensed under the MPL 2.0 license
 * See LICENSE or mozilla.org/en-US/MPL/2.0/
 * github.com/univrsal/input-overlay
 */

#pragma once

#include <obs-module.h>
#include <string>
#include <locale>
#include <uiohook.h>
#include "../util/overlay.hpp"
#include "input_source_settings.hpp"
extern "C" {
#include <graphics/image-file.h>
}


namespace sources
{
    class input_source
    {
    public:
        obs_source_t* m_source = nullptr;

        std::unique_ptr<overlay> m_overlay{};

        std::string m_image_file;
        std::string m_layout_file;

        input_source(obs_source_t* source, obs_data_t* settings) :
            m_source(source)
        {
            m_overlay = std::make_unique<overlay>();
            obs_source_update(m_source, settings);
        }

        ~input_source()
        {
            m_overlay.reset(nullptr);
        };

        void load_overlay() const;

        inline void update(obs_data_t* settings);
        inline void tick(float seconds);
        inline void render(gs_effect_t* effect) const;
    };

    static bool is_controller_changed(obs_properties_t* props, obs_property_t* p, obs_data_t* s);

    static bool is_mouse_changed(obs_properties_t* props, obs_property_t* p, obs_data_t* s);

    static bool use_monitor_center_changed(obs_properties_t* props, obs_property_t* p, obs_data_t* s);

    /* For registering */
    static obs_properties_t* get_properties_for_overlay(void* data);

    void register_overlay_source();
}