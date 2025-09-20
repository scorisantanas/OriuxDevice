import subprocess
import os
import sys

# Define font sizes and output paths
font_sizes = [12, 14, 16, 20, 42]
output_path = "weather"
font_path = "D:/O365/SharePoint/Design/Typo_Grotesk_Rounded_pro/Typo Grotesk Rounded.otf"

# Read required characters from file
with open(os.path.join(output_path, "required_chars.txt"), "r", encoding="utf-8") as f:
    required_chars = f.read().strip()

# Generate fonts
for size in font_sizes:
    output_file = os.path.join(output_path, f"lv_font_typo_grotesk_rounded_{size}.c")
    command = [
        "npx", "lv_font_conv",
        "--font", font_path,
        "--size", str(size),
        "--format", "lvgl",
        "--bpp", "4",
        "--no-compress",
        "--range", "0x20-0x7F,0x0100-0x017F,0xB0",  # Basic Latin + Latin Extended-A + Degree Symbol
        "--symbols", required_chars,
        "-o", output_file
    ]
    
    # On Windows, use shell=True to allow the system to find npx.cmd
    is_windows = sys.platform == "win32"
    
    try:
        print(f"Generating font size {size}...")
        subprocess.run(command, check=True, shell=is_windows, capture_output=True, text=True)
        
        # Post-process the file to fix the include path
        with open(output_file, 'r', encoding='utf-8') as f:
            content = f.read()
        
        content = content.replace('#include "lvgl/lvgl.h"', '#include <lvgl.h>')
        
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(content)
            
        print(f"Successfully generated and patched {output_file}")
    except subprocess.CalledProcessError as e:
        print(f"Error generating font size {size}:")
        print(f"STDOUT: {e.stdout}")
        print(f"STDERR: {e.stderr}")
        sys.exit(1)
    except FileNotFoundError:
        print(f"Error: 'npx' command not found. Please ensure Node.js and npm are installed and in your system's PATH.")
        sys.exit(1)

print("Font generation complete.")