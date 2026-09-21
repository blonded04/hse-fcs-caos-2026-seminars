import java.lang.management.GarbageCollectorMXBean;
import java.lang.management.ManagementFactory;
import java.util.List;
import java.util.Locale;

public final class ManagedAllocation {
    static final int BATCH_SIZE = 1024;
    // Публикация в массиве не даёт свести работу к одним вычислениям полей.
    static final Pair[] objects = new Pair[BATCH_SIZE];
    static volatile long sink;

    static final class Pair {
        final long a, b;
        Pair(long a, long b) {
            this.a = a;
            this.b = b;
        }
    }

    static long run(int batches) {
        long checksum = 0;
        for (int batch = 0; batch < batches; ++batch) {
            for (int i = 0; i < BATCH_SIZE; ++i) {
                long n = (long)batch * BATCH_SIZE + i;
                objects[i] = new Pair(n, n ^ 0x12345678L);
            }
            for (int i = 0; i < BATCH_SIZE; ++i)
                checksum += objects[i].a + objects[i].b;
            // Объекты становятся недостижимыми; GC работает во время run().
            for (int i = 0; i < BATCH_SIZE; ++i)
                objects[i] = null;
        }
        sink = checksum;
        return checksum;
    }

    static long gcCount(List<GarbageCollectorMXBean> collectors) {
        long count = 0;
        for (var collector : collectors)
            count += Math.max(0, collector.getCollectionCount());
        return count;
    }

    public static void main(String[] args) {
        Locale.setDefault(Locale.ROOT);
        if (args.length > 1)
            throw new IllegalArgumentException("usage: ManagedAllocation [batches]");
        int batches = args.length == 1 ? Integer.parseInt(args[0]) : 500000;
        if (batches < 1 || batches > 1000000)
            throw new IllegalArgumentException("batches must be in 1..1000000");

        var threadBean = (com.sun.management.ThreadMXBean)
                ManagementFactory.getThreadMXBean();
        if (!threadBean.isThreadAllocatedMemorySupported())
            throw new IllegalStateException("HotSpot allocation counter unavailable");
        threadBean.setThreadAllocatedMemoryEnabled(true);
        long threadId = Thread.currentThread().threadId();
        var collectors = ManagementFactory.getGarbageCollectorMXBeans();

        // Как в C, 10 240 000 объектов для прогрева. Несколько вызовов греют JIT.
        for (int i = 0; i < 10; ++i)
            run(1000);
        long gcBefore = gcCount(collectors);
        long bytesBefore = threadBean.getThreadAllocatedBytes(threadId);
        long start = System.nanoTime();
        long checksum = run(batches);
        double elapsedMs = (System.nanoTime() - start) / 1e6;
        long allocatedBytes = threadBean.getThreadAllocatedBytes(threadId) - bytesBefore;
        long collections = gcCount(collectors) - gcBefore;
        long count = (long)batches * BATCH_SIZE;

        System.out.printf("Java: objects=%d elapsed_ms=%.3f checksum=%d%n",
                          count, elapsedMs, checksum);
        // Счётчики подтверждают реальные выделения и GC внутри измеряемой фазы.
        System.out.printf("allocated_bytes=%d bytes_per_object=%.1f gc_count=%d%n",
                          allocatedBytes, (double)allocatedBytes / count, collections);
    }
}
