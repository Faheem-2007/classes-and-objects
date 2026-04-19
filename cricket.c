#include <stdio.h>

int main()
{
    int N, M, T;
    scanf("%d %d %d", &N, &M, &T);
    if (N <= 0 || N > 5 || M <= 0 || M > 3 || T < 1 || T > 3)
    {
        {
            printf("Check the player details.\n");
            return 0;
        }
        int total_innings = N + M;
        int player_scores[3][8];
        double averages[3];
        for (int i = 0; i < T; i++)
        {
            double sum = 0;
            for (int j = 0; j < total_innings; j++)
            {
                scanf("%d", &player_scores[i][j]);
                sum += player_scores[i][j];
            }
            averages[i] = sum / total_innings;
        }
        int winner = 0;
        double max_avg = averages[0];
        for (int i = 1; i < T; i++)
        {
            if (averages[i] > max_avg)
            {
                max_avg = averages[i];
                winner = i;
            }
        }
        printf("Player-%d won Man of the Match with a secured average of %.2f.\n", winner + 1, max_avg);
        return 0;
    }
}