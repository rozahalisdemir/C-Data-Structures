#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6  // Graf üzerindeki düğüm sayısı
#define INF INT_MAX

// En küçük mesafeye sahip henüz ziyaret edilmemiş düğümü bulur
int minDistance(int dist[], bool visited[]) {
    int min = INF, min_index = 0;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Yolu yazdıran yardımcı fonksiyon
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);
    printf(" -> %d", j);
}


void printSolution(int dist[], int parent[], int src) {
    printf("\nDugum\tMesafe\t\tYol\n");
    printf("---------------------------------------------\n");

    for (int i = 0; i < V; i++) {
        printf("%d\t", i);
        if (dist[i] == INF) {
            printf("ULASILAMAZ\t");
        } else {
            printf("%d\t\t", dist[i]);
        }

        if (dist[i] != INF) {
            printf("%d", src);
            if (dist[i] != 0) {
                printPath(parent, i);
            }
        }
        printf("\n");
    }
}

// Dijkstra Algoritması - Adjacency Matrix kullanarak
void dijkstra(int graph[V][V], int src) {
    int dist[V];      // Kaynak düğümden her düğüme olan en kısa mesafe
    bool visited[V];  // Ziyaret edilen düğümleri takip eder
    int parent[V];    // Yolu saklar

    // Başlangıç değerlerini ata
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    // Kaynak düğümün mesafesi 0
    dist[src] = 0;

    // Tüm düğümler için en kısa yolu bul
    for (int count = 0; count < V - 1; count++) {
        // Henüz işlenmemiş düğümler arasından en küçük mesafeye sahip olanı seç
        int u = minDistance(dist, visited);

        // Seçilen düğümü ziyaret edildi olarak işaretle
        visited[u] = true;

        // Seçilen düğümün komşu düğümlerinin mesafelerini güncelle
        for (int v = 0; v < V; v++) {
            // dist[v]'yi güncelle sadece:
            // 1. Henüz ziyaret edilmemişse
            // 2. u'dan v'ye bir kenar varsa
            // 3. u üzerinden giden toplam ağırlık dist[v]'den küçükse
            if (!visited[v] &&
                graph[u][v] != 0 &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }


    printSolution(dist, parent, src);
}

int main() {
    /* Örnek Graf (Adjacency Matrix):

         (0)---4---(1)---8---(2)
          |         |         |\
          8         11        | 7
          |         |         |  \
         (7)---1---(8)---2---(3)  4
          |         |         |   |
          7         6         9   |
          |         |         |   |
         (6)---2---(5)--10---(4)--+

    Bu 6 düğümlü basit versiyonu:

         (0)---4---(1)---8---(2)
                           / |
                         7   4
                        /    |
                      (3)---9---(4)
                        |
                       14
                        |
                      (5)---10--+
    */

    //  6x6 matris - simetrik graf
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},      // 0'dan: 1'e 4
        {4, 0, 8, 0, 0, 0},      // 1'den: 0'a 4, 2'ye 8
        {0, 8, 0, 7, 4, 0},      // 2'den: 1'e 8, 3'e 7, 4'e 4
        {0, 0, 7, 0, 9, 14},     // 3'den: 2'ye 7, 4'e 9, 5'e 14
        {0, 0, 4, 9, 0, 10},     // 4'den: 2'ye 4, 3'e 9, 5'e 10
        {0, 0, 0, 14, 10, 0}     // 5'den: 3'e 14, 4'e 10
    };

    printf("Dijkstra Algoritmasi - Adjacency Matrix Kullanarak\n");
    printf("==================================================\n");

    int source = 0;
    printf("\nKaynak dugum: %d\n", source);

    dijkstra(graph, source);

    printf("\n\nFarkli kaynak ile test:\n");
    dijkstra(graph, 2);

    return 0;
}
