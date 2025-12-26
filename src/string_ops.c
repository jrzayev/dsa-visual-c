#include "dsa_visual.h"

StringBuilder* string_create(const char* initial) {
    StringBuilder* sb = (StringBuilder*)malloc(sizeof(StringBuilder));
    
    if (initial == NULL) {
        sb->capacity = 16;
        sb->data = (char*)malloc(sb->capacity);
        sb->data[0] = '\0';
        sb->length = 0;
    } else {
        sb->length = strlen(initial);
        sb->capacity = sb->length + 16;
        sb->data = (char*)malloc(sb->capacity);
        strcpy(sb->data, initial);
    }
    
    printf(GREEN "✓ Created string: \"%s\"\n" RESET, sb->data);
    return sb;
}

static void string_ensure_capacity(StringBuilder* sb, int min_capacity) {
    if (sb->capacity < min_capacity) {
        int new_capacity = sb->capacity * 2;
        if (new_capacity < min_capacity) {
            new_capacity = min_capacity;
        }
        
        printf(YELLOW "  ⚡ Expanding capacity: %d → %d\n" RESET, sb->capacity, new_capacity);
        
        char* new_data = (char*)malloc(new_capacity);
        strcpy(new_data, sb->data);
        free(sb->data);
        sb->data = new_data;
        sb->capacity = new_capacity;
    }
}

void string_append(StringBuilder* sb, const char* str) {
    printf(CYAN "Appending \"%s\"\n" RESET, str);
    
    int str_len = strlen(str);
    string_ensure_capacity(sb, sb->length + str_len + 1);
    
    strcat(sb->data, str);
    sb->length += str_len;
    
    printf(GREEN "✓ Result: \"%s\"\n" RESET, sb->data);
    string_visualize(sb);
}

void string_append_char(StringBuilder* sb, char c) {
    printf(CYAN "Appending char '%c'\n" RESET, c);
    
    string_ensure_capacity(sb, sb->length + 2);
    
    sb->data[sb->length++] = c;
    sb->data[sb->length] = '\0';
    
    printf(GREEN "✓ Result: \"%s\"\n" RESET, sb->data);
    string_visualize(sb);
}

void string_insert(StringBuilder* sb, int index, const char* str) {
    if (index < 0 || index > sb->length) {
        printf(RED "✗ Invalid index %d (length: %d)\n" RESET, index, sb->length);
        return;
    }
    
    printf(CYAN "Inserting \"%s\" at index %d\n" RESET, str, index);
    
    int str_len = strlen(str);
    string_ensure_capacity(sb, sb->length + str_len + 1);
    
    memmove(sb->data + index + str_len, sb->data + index, sb->length - index + 1);
    memcpy(sb->data + index, str, str_len);
    sb->length += str_len;
    
    printf(GREEN "✓ Result: \"%s\"\n" RESET, sb->data);
    string_visualize(sb);
}

void string_delete(StringBuilder* sb, int start, int end) {
    if (start < 0 || end > sb->length || start >= end) {
        printf(RED "✗ Invalid range [%d, %d) (length: %d)\n" RESET, start, end, sb->length);
        return;
    }
    
    printf(CYAN "Deleting characters [%d, %d)\n" RESET, start, end);
    printf("  Removing: \"%.*s\"\n", end - start, sb->data + start);
    
    memmove(sb->data + start, sb->data + end, sb->length - end + 1);
    sb->length -= (end - start);
    
    printf(GREEN "✓ Result: \"%s\"\n" RESET, sb->data);
    string_visualize(sb);
}

char string_char_at(StringBuilder* sb, int index) {
    if (index < 0 || index >= sb->length) {
        printf(RED "✗ Index %d out of bounds (length: %d)\n" RESET, index, sb->length);
        return '\0';
    }
    
    printf(GREEN "✓ charAt(%d) = '%c'\n" RESET, index, sb->data[index]);
    return sb->data[index];
}

int string_index_of(StringBuilder* sb, const char* substr) {
    printf(CYAN "Searching for \"%s\"\n" RESET, substr);
    
    int substr_len = strlen(substr);
    
    for (int i = 0; i <= sb->length - substr_len; i++) {
        printf("  Position %d: checking \"%.*s\"\n", i, substr_len, sb->data + i);
        usleep(200000);
        
        if (strncmp(sb->data + i, substr, substr_len) == 0) {
            printf(GREEN "✓ Found \"%s\" at index %d\n" RESET, substr, i);
            return i;
        }
    }
    
    printf(RED "✗ Substring \"%s\" not found\n" RESET, substr);
    return -1;
}

void string_replace(StringBuilder* sb, const char* old_str, const char* new_str) {
    printf(CYAN "Replacing \"%s\" with \"%s\"\n" RESET, old_str, new_str);
    
    int old_len = strlen(old_str);
    int new_len = strlen(new_str);
    int count = 0;
    
    char* pos = sb->data;
    while ((pos = strstr(pos, old_str)) != NULL) {
        count++;
        pos += old_len;
    }
    
    if (count == 0) {
        printf(YELLOW "⚠ No occurrences found\n" RESET);
        return;
    }
    
    int new_length = sb->length + count * (new_len - old_len);
    char* new_data = (char*)malloc(new_length + 1);
    
    char* src = sb->data;
    char* dst = new_data;
    
    while (*src) {
        if (strncmp(src, old_str, old_len) == 0) {
            memcpy(dst, new_str, new_len);
            dst += new_len;
            src += old_len;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    
    free(sb->data);
    sb->data = new_data;
    sb->length = new_length;
    sb->capacity = new_length + 1;
    
    printf(GREEN "✓ Replaced %d occurrence(s)\n" RESET, count);
    printf(GREEN "✓ Result: \"%s\"\n" RESET, sb->data);
    string_visualize(sb);
}

void string_reverse(StringBuilder* sb) {
    printf(CYAN "Reversing string\n" RESET);
    
    int left = 0, right = sb->length - 1;
    
    while (left < right) {
        printf("  Swapping [%d]='%c' ↔ [%d]='%c'\n", 
               left, sb->data[left], right, sb->data[right]);
        
        char temp = sb->data[left];
        sb->data[left] = sb->data[right];
        sb->data[right] = temp;
        
        left++;
        right--;
        usleep(200000);
    }
    
    printf(GREEN "✓ Result: \"%s\"\n" RESET, sb->data);
    string_visualize(sb);
}

void string_to_upper(StringBuilder* sb) {
    printf(CYAN "Converting to uppercase\n" RESET);
    
    for (int i = 0; i < sb->length; i++) {
        if (sb->data[i] >= 'a' && sb->data[i] <= 'z') {
            sb->data[i] -= 32;
        }
    }
    
    printf(GREEN "✓ Result: \"%s\"\n" RESET, sb->data);
    string_visualize(sb);
}

void string_to_lower(StringBuilder* sb) {
    printf(CYAN "Converting to lowercase\n" RESET);
    
    for (int i = 0; i < sb->length; i++) {
        if (sb->data[i] >= 'A' && sb->data[i] <= 'Z') {
            sb->data[i] += 32;
        }
    }
    
    printf(GREEN "✓ Result: \"%s\"\n" RESET, sb->data);
    string_visualize(sb);
}

void string_trim(StringBuilder* sb) {
    printf(CYAN "Trimming whitespace\n" RESET);
    
    int start = 0;
    while (start < sb->length && (sb->data[start] == ' ' || sb->data[start] == '\t' || 
           sb->data[start] == '\n' || sb->data[start] == '\r')) {
        start++;
    }
    
    int end = sb->length - 1;
    while (end > start && (sb->data[end] == ' ' || sb->data[end] == '\t' || 
           sb->data[end] == '\n' || sb->data[end] == '\r')) {
        end--;
    }
    
    int new_length = end - start + 1;
    
    if (start > 0) {
        memmove(sb->data, sb->data + start, new_length);
    }
    sb->data[new_length] = '\0';
    sb->length = new_length;
    
    printf(GREEN "✓ Result: \"%s\"\n" RESET, sb->data);
    string_visualize(sb);
}

StringBuilder* string_substring(StringBuilder* sb, int start, int end) {
    if (start < 0 || end > sb->length || start >= end) {
        printf(RED "✗ Invalid range [%d, %d) (length: %d)\n" RESET, start, end, sb->length);
        return NULL;
    }
    
    printf(CYAN "Extracting substring [%d, %d)\n" RESET, start, end);
    
    int len = end - start;
    char* temp = (char*)malloc(len + 1);
    strncpy(temp, sb->data + start, len);
    temp[len] = '\0';
    
    StringBuilder* result = string_create(temp);
    free(temp);
    
    return result;
}

int string_is_palindrome(StringBuilder* sb) {
    printf(CYAN "Checking if \"%s\" is a palindrome\n" RESET, sb->data);
    
    int left = 0, right = sb->length - 1;
    
    while (left < right) {
        printf("  Comparing [%d]='%c' with [%d]='%c'\n", 
               left, sb->data[left], right, sb->data[right]);
        usleep(300000);
        
        if (sb->data[left] != sb->data[right]) {
            printf(RED "✗ Not a palindrome\n" RESET);
            return 0;
        }
        left++;
        right--;
    }
    
    printf(GREEN "✓ \"%s\" is a palindrome!\n" RESET, sb->data);
    return 1;
}

void string_visualize(StringBuilder* sb) {
    printf("\n" CYAN "String (Length: %d, Capacity: %d):\n" RESET, sb->length, sb->capacity);
    
    printf("  \"");
    for (int i = 0; i < sb->length; i++) {
        if (sb->data[i] == ' ') {
            printf(BG_YELLOW "·" RESET);
        } else if (sb->data[i] == '\n') {
            printf(BG_RED "↵" RESET);
        } else if (sb->data[i] == '\t') {
            printf(BG_RED "→" RESET);
        } else {
            printf("%c", sb->data[i]);
        }
    }
    printf("\"\n");
    
    printf("  ");
    for (int i = 0; i < sb->length && i < 50; i++) {
        printf(BG_BLUE " %c " RESET, sb->data[i]);
    }
    if (sb->length > 50) {
        printf("...");
    }
    printf("\n");
    
    printf("  ");
    for (int i = 0; i < sb->length && i < 50; i++) {
        printf("%2d  ", i);
    }
    printf("\n\n");
}

void string_free(StringBuilder* sb) {
    free(sb->data);
    free(sb);
}
