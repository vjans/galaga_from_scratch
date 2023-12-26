#include "textUtils.h"


unsigned const int chars[46] = {
    // A
    0b00100 | 0b01010 << 5 | 0b10001 << 10 | 0b11111 << 15 | 0b10001 << 20,
    // B
    0b11110 | 0b10001 << 5 | 0b11110 << 10 | 0b10001 << 15 | 0b11110 << 20,
    // C
    0b01110 | 0b10001 << 5 | 0b10000 << 10 | 0b10001 << 15 | 0b01110 << 20,
    // D
    0b11110 | 0b10001 << 5 | 0b10001 << 10 | 0b10001 << 15 | 0b11110 << 20,
    // E
    0b11111 | 0b10000 << 5 | 0b11110 << 10 | 0b10000 << 15 | 0b11111 << 20,
    // F
    0b11111 | 0b10000 << 5 | 0b11110 << 10 | 0b10000 << 15 | 0b10000 << 20,
    // G
    0b01110 | 0b10001 << 5 | 0b10000 << 10 | 0b10011 << 15 | 0b01110 << 20,
    // H
    0b10001 | 0b10001 << 5 | 0b11111 << 10 | 0b10001 << 15 | 0b10001 << 20,
    // I
    0b01110 | 0b00100 << 5 | 0b00100 << 10 | 0b00100 << 15 | 0b01110 << 20,
    // J
    0b00111 | 0b00010 << 5 | 0b00010 << 10 | 0b10010 << 15 | 0b01100 << 20,
    // K
    0b10001 | 0b10010 << 5 | 0b11100 << 10 | 0b10010 << 15 | 0b10001 << 20,
    // L
    0b10000 | 0b10000 << 5 | 0b10000 << 10 | 0b10000 << 15 | 0b11111 << 20,
    // M
    0b10001 | 0b11011 << 5 | 0b10101 << 10 | 0b10001 << 15 | 0b10001 << 20,
    // N
    0b10001 | 0b11001 << 5 | 0b10101 << 10 | 0b10011 << 15 | 0b10001 << 20,
    // O
    0b01110 | 0b10001 << 5 | 0b10001 << 10 | 0b10001 << 15 | 0b01110 << 20,
    // P
    0b11110 | 0b10001 << 5 | 0b11110 << 10 | 0b10000 << 15 | 0b10000 << 20,
    // Q
    0b01110 | 0b10001 << 5 | 0b10101 << 10 | 0b10010 << 15 | 0b01101 << 20,
    // R
    0b11110 | 0b10001 << 5 | 0b11110 << 10 | 0b10010 << 15 | 0b10001 << 20,
    // S
    0b01111 | 0b10000 << 5 | 0b01110 << 10 | 0b00001 << 15 | 0b11110 << 20,
    // T
    0b11111 | 0b00100 << 5 | 0b00100 << 10 | 0b00100 << 15 | 0b00100 << 20,
    // U
    0b10001 | 0b10001 << 5 | 0b10001 << 10 | 0b10001 << 15 | 0b01110 << 20,
    // V
    0b10001 | 0b10001 << 5 | 0b10001 << 10 | 0b01010 << 15 | 0b00100 << 20,
    // W
    0b10001 | 0b10001 << 5 | 0b10101 << 10 | 0b10101 << 15 | 0b01010 << 20,
    // X
    0b10001 | 0b01010 << 5 | 0b00100 << 10 | 0b01010 << 15 | 0b10001 << 20,
    // Y
    0b10001 | 0b01010 << 5 | 0b00100 << 10 | 0b00100 << 15 | 0b00100 << 20,
    // Z
    0b11111 | 0b00010 << 5 | 0b00100 << 10 | 0b01000 << 15 | 0b11111 << 20,
    
     // Digits 0-9
    0b01110 | 0b10001 << 5 | 0b10101 << 10 | 0b10001 << 15 | 0b01110 << 20, // 0
    0b00100 | 0b01100 << 5 | 0b00100 << 10 | 0b00100 << 15 | 0b01110 << 20, // 1
    0b11110 | 0b00001 << 5 | 0b01110 << 10 | 0b10000 << 15 | 0b11111 << 20, // 2
    0b11111 | 0b00001 << 5 | 0b01110 << 10 | 0b00001 << 15 | 0b11110 << 20, // 3
    0b10000 | 0b10000 << 5 | 0b10001 << 10 | 0b11111 << 15 | 0b00001 << 20, // 4
    0b11111 | 0b10000 << 5 | 0b11110 << 10 | 0b00001 << 15 | 0b11110 << 20, // 5
    0b01110 | 0b10000 << 5 | 0b11110 << 10 | 0b10001 << 15 | 0b01110 << 20, // 6
    0b11111 | 0b00001 << 5 | 0b00010 << 10 | 0b00100 << 15 | 0b01000 << 20, // 7
    0b01110 | 0b10001 << 5 | 0b01110 << 10 | 0b10001 << 15 | 0b01110 << 20, // 8
    0b01110 | 0b10001 << 5 | 0b01111 << 10 | 0b00001 << 15 | 0b01110 << 20, // 9

    // Special characters !?+-():/=
    0b00100 | 0b00100 << 5 | 0b00100 << 10 | 0b00000 << 15 | 0b00100 << 20, // !
    0b01110 | 0b00010 << 5 | 0b00100 << 10 | 0b00000 << 15 | 0b00100 << 20, // ?
    0b00000 | 0b00100 << 5 | 0b01110 << 10 | 0b00100 << 15 | 0b00000 << 20, // +
    0b00000 | 0b00000 << 5 | 0b01110 << 10 | 0b00000 << 15 | 0b00000 << 20, // -
    0b00010 | 0b00100 << 5 | 0b01000 << 10 | 0b00100 << 15 | 0b00010 << 20, // (
    0b01000 | 0b00100 << 5 | 0b00010 << 10 | 0b00100 << 15 | 0b01000 << 20, // )
    0b00000 | 0b00000 << 5 | 0b00100 << 10 | 0b00000 << 15 | 0b00100 << 20, // :
    0b00001 | 0b00010 << 5 | 0b00100 << 10 | 0b01000 << 15 | 0b10000 << 20, // /
    0b00000 | 0b11111 << 5 | 0b00000 << 10 | 0b11111 << 15 | 0b00000 << 20, // =
    0b00000 | 0b00000 << 5 | 0b00000 << 10 | 0b00000 << 15 | 0b00100 << 20, // .

};

unsigned int get_char_bitmap(char ch) {
    // Convert lowercase to uppercase
    if (ch >= 'a' && ch <= 'z') {
        ch -= 32; // ASCII difference between lowercase and uppercase
    }

    // Check if the character is a letter
    if (ch >= 'A' && ch <= 'Z') {
        return chars[ch - 'A']; // Letters are at the beginning of the array
    }

    // Check if the character is a digit
    if (ch >= '0' && ch <= '9') {
        return chars[26 + ch - '0']; // Digits start after 26 letters
    }

    // Check for special characters
    switch (ch) {
        case '!': return chars[36];
        case '?': return chars[37];
        case '+': return chars[38];
        case '-': return chars[39];
        case '(': return chars[40];
        case ')': return chars[41];
        case ':': return chars[42];
        case '/': return chars[43];
        case '=': return chars[44];
        case '.': return chars[45];
        default:  return 0; // Return 0 for characters not in the array
    }
}
void write_letter(char letter, v3 pos, float scale) {
    unsigned int bitmap = get_char_bitmap(letter);

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            // Flipping the bitmap vertically and horizontally
            int flipped_row = 4 - row; // Flipping row index
            int flipped_col = 4 - col; // Flipping column index

            if (bitmap & (1 << (flipped_row * 5 + flipped_col))) {
                float x_pos = pos.x + col * scale;
                float y_pos = pos.y + row * scale;
                float z_pos = pos.z;

                // Draw the quad
                glBegin(GL_QUADS);
                    glVertex3f(x_pos, y_pos, z_pos);
                    glVertex3f(x_pos + scale, y_pos, z_pos);
                    glVertex3f(x_pos + scale, y_pos + scale, z_pos);
                    glVertex3f(x_pos, y_pos + scale, z_pos);
                glEnd();
            }
        }
    }
}

void write_text(const std::string& text, v3 pos, float scale, const v3& color) {
    glCol(color);

    float x_offset = 0;
    float y_offset = 0;
    for (std::string::size_type i = 0; i < text.length(); ++i) {
        if (text[i] == '\n') {
            // Newline character: move down one line and reset x offset
            y_offset += scale * 6;
            x_offset = 0;
        } else {
            // Normal character: write it and move to the next position
            char letter = text[i];
            v3 letter_pos = { pos.x + x_offset, pos.y - y_offset, pos.z }; // Adjust y-position for new lines
            write_letter(letter, letter_pos, scale);
            x_offset += scale * 6; // Move to the next character position
        }
    }
}
