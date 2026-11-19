#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MIN_NUM 1
#define MAX_NUM 69
#define PICK_COUNT 7
#define MAX_SETS 5

void generate_lotto_set(int nums[PICK_COUNT]) {
    int used[MAX_NUM + 1] = {0};
    int count = 0;

    while (count < PICK_COUNT) {
        int r = rand() % (MAX_NUM - MIN_NUM + 1) + MIN_NUM;
        if (!used[r]) {
            used[r] = 1;
            nums[count++] = r;
        }
    }
}

int main(void) {
    int n = 0;

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩:");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SETS) {
        printf("輸入組數無效（請輸入 1 到 5 之間的整數）。\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    if (time_str != NULL) {
        size_t len = strlen(time_str);
        if (len > 0 && time_str[len - 1] == '\n') {
            time_str[len - 1] = '\0';
        }
    }

    FILE *fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        printf("無法開啟 lotto.txt 進行寫入。\n");
        return 1;
    }

    fprintf(fp, "= lotto649 =\n");
    fprintf(fp, "= %s =\n", time_str ? time_str : "Unknown Time");

    for (int i = 1; i <= MAX_SETS; i++) {
        fprintf(fp, "[%d]: ", i);
        if (i <= n) {
            int set[PICK_COUNT];
            generate_lotto_set(set);
            for (int j = 0; j < PICK_COUNT; j++) {
                fprintf(fp, "%02d%s", set[j], (j < PICK_COUNT - 1) ? " " : "");
            }
            fprintf(fp, "\n");
        } else {
            for (int j = 0; j < PICK_COUNT; j++) {
                fprintf(fp, "--%s", (j < PICK_COUNT - 1) ? " " : "");
            }
            fprintf(fp, "\n");
        }
    }

    fprintf(fp, "======== csie@cgu =========\n");

    fclose(fp);
    printf("已為您購買的%d組樂透組合輸出至 lotto.txt\n", n);

    return 0;
}
