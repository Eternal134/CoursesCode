class CPU {
    private int speed;

    public CPU() {
        // 默认构造函数
    }

    public CPU(int _speed) {
        // 构造函数
        this.speed = _speed;
    }

    public int getSpeed() {
        return speed;
    }

    public void setSpeed(int _speed) {
        speed = _speed;
    }
}

class HardDisk {
    private int amount;

    public HardDisk() {
    }

    public HardDisk(int _amount) {
        this.amount = _amount;
    }

    public int getAmount() {
        return amount;
    }

    public void setAmount(int _amount) {
        amount = _amount;
    }
}

class PC {
    // mistake: 定义类时忘了初始化
    private CPU cpu = new CPU();
    private HardDisk HD = new HardDisk();

    public void setCPU(CPU c) {
        cpu.setSpeed(c.getSpeed());;
    }

    public void setHardDisk(HardDisk h) {
        HD.setAmount(h.getAmount());
    }

    public void show() {
        System.out.println("CPU's speed:\t" + cpu.getSpeed());
        System.out.println("HardDisk's amount:\t" + HD.getAmount());
    }
}

public class Test_ex2 {
    public static void main(String args[]) {
        CPU cpu = new CPU(2200);
        HardDisk HD = new HardDisk(200);
        PC pc = new PC();
        pc.setCPU(cpu);
        pc.setHardDisk(HD);
        pc.show();
    }
}
