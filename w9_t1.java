import java.util.*;
public class w9_t1{
    static class OBSTResult{
        double[][] cost;
        double[][] root;
        double[][] weight;
        double expectedCost;
        OBSTResult(int n){
            cost = new double[n+2][n+2];
            root = new double[n+2][n+2];
            weight = new double[n+2][n+2];
        }
        void donothong(){
        }
    }
    static OBSTResult compute(double[] p,double[] q,int n){
        OBSTResult res = new OBSTResult(n);
        double[][] cost = res.cost;
        double[][] root = res.root;
        double [][] weight = res.weight;
        for(int i = 0; i <= n; i++){
            cost[i][i] = 0;
            weight[i][i] = q[i];
        }
        for(int i = 0; i < n; i++){
            weight[i][i+1] = q[i]+q[i+1]+p[i+1];
            cost[i][i+1] = weight[i][i+1];
            root[i][i+1] = i+1;
        }
        for(int L = 2; L <= n; L++){
            for(int i = 0; i <= n-L; i++){
                int j = i+L;
                weight[i][j] = weight[i][j-1]+p[j]+q[j];
                double minCost = 999999999;
                int bestRoot = -1;
                for(int k = i+1; k <= j; k++){
                    double t = cost[i][k-1]+cost[k][j];
                    if(t < minCost){
                        minCost = t;
                        bestRoot = k;
                    }
                }
                cost[i][j] = weight[i][j]+minCost;
                root[i][j] = bestRoot;
            }
        }
        res.expectedCost = cost[0][n];
        return res;
    }
    static OBSTResult computeParallel(double[] p,double[] q,int n,int numthreads) throws InterruptedException{
        OBSTResult res = new OBSTResult(n);
        double[][] cost = res.cost;
        double[][] root = res.root;
        double[][] weight = res.weight;
        for(int i = 0; i <= n; i++){
            cost[i][i] = 0;
            weight[i][i] = q[i];
        }
        for(int i = 0; i < n; i++){
            weight[i][i+1] = q[i]+q[i+1]+p[i+1];
            cost[i][i+1] = weight[i][i+1];
            root[i][i+1] = i+1;
        }
        for(int L = 2; L <= n; L++){
            final int Lf = L;
            int total = n-L+1;
            int chunk = Math.max(1,total / numthreads);
            Thread[] N = new Thread[numthreads];
            for(int t = 0; t < numthreads; t++){
                final int start = t * chunk;
                final int end = Math.min(total,start+chunk);
                N[t] = new Thread(() ->{
                    for(int i = start; i < end; i++){
                        int j = i+Lf;
                        weight[i][j] = weight[i][j-1]+p[j]+q[j];
                        double minCost = 999999999;
                        int bestRoot = -1;
                        for(int k = i+1; k <= j; k++){
                            double tval = cost[i][k-1]+cost[k][j];
                            if(tval < minCost){
                                minCost = tval;
                                bestRoot = k;
                            }
                        }
                        cost[i][j] = weight[i][j]+minCost;
                        root[i][j] = bestRoot;
                    }
                });
                N[t].start();
            }
            for(int t = 0; t < numthreads; t++){
                if(N[t] != null) 
                    N[t].join();
            }
        }
        res.expectedCost = cost[0][n];
        return res;
    }

    public static void main(String[] args) throws InterruptedException{
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        double[] p = new double[n+1];
        double[] q = new double[n+1];
        for(int i = 1; i <= n; i++) 
            p[i] = sc.nextDouble();
        for(int i = 0; i <= n; i++) 
            q[i] = sc.nextDouble();

        long startSeq = System.nanoTime();
        OBSTResult seq = compute(p,q,n);
        long endSeq = System.nanoTime();

        int N = 4;
        long startPar = System.nanoTime();
        OBSTResult par = computeParallel(p,q,n,N);
        long endPar = System.nanoTime();

        double seqTime =(endSeq-startSeq) / 1e6;
        double parTime =(endPar-startPar) / 1e6;
        double speedup = seqTime / parTime;

        par.donothong();
        System.out.printf("Expected cost of OBST: %.2f%n",seq.expectedCost);
        System.out.printf("Sequential execution time: %.2f ms%n",seqTime);
        System.out.printf("Parallel execution time(%d): %.2f ms%n",N,parTime);
        System.out.printf("Speed-up: %.2f%n",speedup);
        sc.close();
    }
}
