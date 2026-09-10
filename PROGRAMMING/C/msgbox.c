#include <windows.h>

// Função principal do programa
int main() {
    // Obtém a instância do programa
    HINSTANCE hInstance = GetModuleHandle(NULL);

    // Cria uma janela invisível (não é realmente necessária para exibir MessageBox)
    HWND hWnd = CreateWindowEx(0, "STATIC", NULL, 0, 0, 0, 0, 0, HWND_DESKTOP, NULL, hInstance, NULL);

    // Exibe a MessageBox
    MessageBox(hWnd, "Hello, World!", "MessageBox from Windows API", MB_OK | MB_ICONINFORMATION);

    // Limpa recursos
    DestroyWindow(hWnd);

    return 0;
}

