import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Day4 {
    public static int calculatePointTotal(String filename) {
        // We want to read the file line by line.
        int sum = 0;

        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line;
            while ((line = br.readLine()) != null) {
                // process the line.
                sum += processLine(line);
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }    
        
        return sum;
    }

    public static int processLine(String line) {
        int exponent = 0;
        int currentValue = 0;
        // We want to remove the first part in the form of "Card X: ".
        line = line.split(": ")[1];

        // Now our string looks like "___ ___ ___ ___ ___ | ___ ___ ___ ...", and we'll split by " | ".
        String[] parts = line.split(" \\| ");
        
        ArrayList<String> keys = new ArrayList<String>();

        // We process the keys first.

        String[] keyParts = parts[0].split(" ");
        for (String keyPart : keyParts) {
            keys.add(keyPart);
        }

        // Now we process the values.

        String[] valueParts = parts[1].split(" ");
        for (String valuePart : valueParts) {
            if (keys.contains(valuePart)) {
                // We've found a match!
                exponent++;
            }
        }

        return (int) Math.pow(2, exponent - 1);
    }



    public static void main(String[] args) {
        // Tried 168934, too high.
        System.out.println(calculatePointTotal("day4_input.txt"));
    }
}



