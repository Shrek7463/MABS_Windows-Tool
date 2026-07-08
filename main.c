#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* run_powershell_command(const char* command) {
    char full_command[1024];
    snprintf(full_command, sizeof(full_command), "powershell.exe -Command \"%s\"", command);

    // Open the process
    FILE* pipe = _popen(full_command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to open pipe\n");
        return NULL;
    }

    // Read the output
    char buffer[128];
    char* output = malloc(1);
    output[0] = '\0';
    size_t output_size = 1;

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t buffer_len = strlen(buffer);
        output = realloc(output, output_size + buffer_len);
        strcat(output, buffer);
        output_size += buffer_len;
    }

    _pclose(pipe);

    return output;
}

int main() {
    // Prepare for scoop installation
    char* result = run_powershell_command("Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser");
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    // Install Scoop
    result = run_powershell_command("Invoke-RestMethod -Uri https://get.scoop.sh | Invoke-Expression");
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    // Install Git (needed for using scoop)
    result = run_powershell_command("scoop install main/git");
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    // Add extras bucket
    result = run_powershell_command("scoop bucket add extras");
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    // Add nerd fonts bucket
    result = run_powershell_command("scoop bucket add nerd-fonts");
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    // Install vscodium
    result = run_powershell_command("scoop install extras/vscodium");
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    // Install librewolf
    result = run_powershell_command("scoop install extras/librewolf");
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    // Install ttf for jetbrains nerd mono
    result = run_powershell_command("scoop install nerd-fonts/JetBrainsMono-NF-Mono");
    if (result) {
        printf("%s\n", result);
        free(result);
    }

    // Personalised commands

    //    result = run_powershell_command("<YOUR COMMAND GOES HERE>");
    //if (result) {
    //    printf("%s\n", result);
    //    free(result);
    //}

    return 0;
}
