#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h> // bindet auch die System-OpenGL-Header ein (glClear, glViewport …)

#include <cstdio>

static void glfwErrorCallback(int error, const char* description)
{
    std::fprintf(stderr, "GLFW-Fehler %d: %s\n", error, description);
}

int main()
{
    // --- 1. GLFW starten ------------------------------------------------------
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
        return 1;

    // OpenGL 3.3 Core anfordern (passt zu "#version 330" weiter unten)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // --- 2. Fenster + OpenGL-Kontext ------------------------------------------
    // Windows-Skalierung (z. B. 150 %) berücksichtigen
    const float scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow(static_cast<int>(1280 * scale), static_cast<int>(800 * scale),
                                          "N1KA-VISU", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // VSync: höchstens so viele Frames pro Sekunde wie der Monitor Hz hat

    // --- 3. Dear ImGui einrichten ---------------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(scale);
    style.FontScaleDpi = scale;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Zustand der Oberfläche – lebt in DEINEM Code, nicht in ImGui
    bool showDemo = true;
    int clicks = 0;

    // --- 4. Hauptschleife: ein Durchlauf = ein Frame --------------------------
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Minimiert? Dann nichts zeichnen und kurz schlafen
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // UI beschreiben – passiert JEDES Frame komplett neu
        ImGui::Begin("N1KA-VISU");
        ImGui::Text("Hallo aus Dear ImGui %s", IMGUI_VERSION);
        ImGui::Checkbox("Demo-Fenster anzeigen", &showDemo);
        if (ImGui::Button("Klick mich"))
            ++clicks;
        ImGui::SameLine();
        ImGui::Text("Klicks: %d", clicks);
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
        ImGui::End();

        if (showDemo)
            ImGui::ShowDemoWindow(&showDemo);

        // Zeichnen
        ImGui::Render();
        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // --- 5. Aufräumen: umgekehrte Reihenfolge wie beim Einrichten -------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}