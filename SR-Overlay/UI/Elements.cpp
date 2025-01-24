#include <string>

#include "UI.hpp"
#include "../ImGUI/imgui.h"
#include "../Headers/GameData.hpp"

void UI::ShowElements(bool* isMenuOpen) {

    static bool showDemoWindow = false;
    static bool showSpeed = true;
    static bool showFPS = true;

    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle style = ImGui::GetStyle();

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize;

    if (showDemoWindow)
        ImGui::ShowDemoWindow(&showDemoWindow);

    if (*isMenuOpen)
    {
        windowFlags &= ~ImGuiWindowFlags_NoBackground;

        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Menu");

#ifdef _DEBUG
        ImGui::Checkbox("Demo Window", &showDemoWindow);
#endif // _DEBUG

        ImGui::Checkbox("Show speed", &showSpeed);
        ImGui::Checkbox("Show FPS", &showFPS);
        ImGui::DragFloat("Global font scale", &io.FontGlobalScale, 0.005f, 0, 2, "%.2f", ImGuiSliderFlags_AlwaysClamp);

        ImGui::Text("FPS Overlay: %.0f", io.Framerate);
        ImGui::End();
    }

    if (showSpeed) {
        ImGui::Begin("Speed", nullptr, windowFlags);

        // Dynamic scalling, may use this later
        /*
        float textSize = ImGui::GetWindowSize().y;
        textSize = textSize;
        ImGui::GetWindowDrawList()->AddText(io.FontDefault, textSize, ImGui::GetWindowPos(), ImGui::GetColorU32(IM_COL32(255, 255, 255, 255)), std::to_string(static_cast<int>(gameData.playerGroundSpeed)).c_str());
        */

        ImGui::Text("Speed: %.0f", gameData.playerGroundSpeed);
        ImGui::End();
    }

    if (showFPS) {
        ImGui::Begin("FPS", nullptr, windowFlags);
        ImGui::Text("FPS: %.0f", gameData.fps);
        ImGui::End();
    }
    
}