public class WalkerTester {

    public static void main(String[] args) {
        Walker walker = new Walker();
        //WalkerSelfAvoid walker = new WalkerSelfAvoid();

        int nSteps = 0;
        if (args.length > 0)
            nSteps = Integer.parseInt(args[0]);

        walker.walk(nSteps, true);
    }
}
