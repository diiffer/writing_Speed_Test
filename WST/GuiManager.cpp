#include "GuiManager.hpp"
#include "imgui/imgui.h"
#include <iostream>
#include <chrono>

void GuiManager::startTest() {
    if (word_count_ <= 0) return;

    if (test_) delete test_;
    test_ = new TypingTest(current_difficulty_);
    test_->start(word_count_);

    input_buffer_.clear();
    start_time_ = std::chrono::high_resolution_clock::now();
    is_running_ = true;
    is_finished_ = false;
    wpm_ = 0.0f;
    mistakes_ = 0;
}

void GuiManager::stopTest() {
    is_running_ = false;
    is_finished_ = false;
}

int GuiManager::calculateScore(float wpm) {
    if (wpm < 5) return 1;
    if (wpm < 10) return 2;
    if (wpm < 15) return 3;
    if (wpm < 20) return 4;
    return 5;
}

void GuiManager::updateLogic() {
    if (!is_running_ || is_finished_) return;

    TestState state = test_->update(input_buffer_);
    mistakes_ = state.mistakes;

    if (state.is_finished) {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time_;
        if (elapsed.count() > 0) {
            wpm_ = (input_buffer_.length() / 5.0f) / (elapsed.count() / 60.0f);
        } else {
            wpm_ = 0;
        }
        is_running_ = false;
        is_finished_ = true;
    }
}

void GuiManager::render() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Writing Speed Test", nullptr, window_flags);

    float window_width = ImGui::GetWindowWidth();
    float content_width = window_width * 0.7f;
    ImGui::SetCursorPosX((window_width - content_width) * 0.5f);

    if (!is_running_ && !is_finished_) {
        ImGui::Dummy(ImVec2(0, 80));
        ImGui::SetWindowFontScale(2.5f);
        ImGui::TextColored(ImVec4(0.4f, 0.7f, 1.0f, 1.0f), "Writing Speed Test");
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("BMSTU Edition");
        ImGui::Dummy(ImVec2(0, 40));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 20));

        ImGui::SetWindowFontScale(1.8f);
        const char* items[] = { "Easy", "Medium", "Hard" };
        int item_idx = static_cast<int>(current_difficulty_);
        ImGui::SetNextItemWidth(content_width);
        if (ImGui::Combo("Difficulty", &item_idx, items, IM_ARRAYSIZE(items))) {
            current_difficulty_ = static_cast<Difficulty>(item_idx);
        }

        ImGui::SetNextItemWidth(content_width);
        ImGui::InputInt("Word Count", &word_count_);

        if (word_count_ <= 0) {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Please enter a valid number of words!");
        } else if (word_count_ > 500) {
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Dude, are you a robot? Too many words, chill out!");
        }
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Dummy(ImVec2(0, 40));

        bool can_start = (word_count_ > 0 && word_count_ <= 500);
        if (!can_start) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
        if (ImGui::Button("START TEST", ImVec2(content_width, 80))) {
            if (can_start) startTest();
        }
        if (!can_start) ImGui::PopStyleColor();

    } else { // Экран теста или результатов
        ImGui::Dummy(ImVec2(0, 40));
        ImGui::SetWindowFontScale(1.5f);
        ImGui::Text("Target Text:");
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
        ImGui::SetWindowFontScale(2.2f);
        ImGui::PushTextWrapPos(content_width);
        ImGui::TextWrapped("%s", test_->getReference().c_str());
        ImGui::PopTextWrapPos();
        ImGui::SetWindowFontScale(1.0f);
        ImGui::PopStyleColor();

        ImGui::Dummy(ImVec2(0, 40));

        if (is_running_) {
            ImGui::SetWindowFontScale(1.5f);
            ImGui::Text("Type here:");
            ImGui::SetNextItemWidth(content_width);
            char buf[1024] = "";
            strncpy(buf, input_buffer_.c_str(), sizeof(buf));
            ImGui::SetWindowFontScale(1.8f);
            if (ImGui::InputText("##input", buf, IM_ARRAYSIZE(buf))) {
                input_buffer_ = buf;
            }
            ImGui::SetWindowFontScale(1.0f);

            updateLogic();

            ImGui::Dummy(ImVec2(0, 40));
            ImGui::SetWindowFontScale(1.5f);
            ImGui::Text("Mistakes: %d", mistakes_);
            ImGui::SetNextItemWidth(content_width);
            float progress = (float)input_buffer_.length() / test_->getReference().length();
            ImGui::ProgressBar(progress, ImVec2(content_width, 40));
            ImGui::SetWindowFontScale(1.0f);

            ImGui::Dummy(ImVec2(0, 20));
            if (ImGui::Button("Back to Menu", ImVec2(content_width, 40))) {
                stopTest();
            }
        } else if (is_finished_) {
            ImGui::SetWindowFontScale(3.0f);
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "COMPLETED!");
            ImGui::SetWindowFontScale(1.0f);

            ImGui::Dummy(ImVec2(0, 30));
            ImGui::SetWindowFontScale(2.0f);
            ImGui::Text("Your Speed: %.2f WPM", wpm_);
            ImGui::Text("Your Grade: %d/5", calculateScore(wpm_));
            ImGui::Text("Total Mistakes: %d", mistakes_);
            ImGui::SetWindowFontScale(1.0f);

            ImGui::Dummy(ImVec2(0, 40));
            if (ImGui::Button("Back to Menu", ImVec2(content_width, 70))) {
                is_finished_ = false;
                is_running_ = false;
            }
        }
    }
    ImGui::End();
}
