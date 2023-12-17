import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Day4 {
    public static int calculatePointTotal(String filename) {
        // We want to read the file line by line.
        int sum = 0;
        ArrayList<Integer> lineValues = new ArrayList<Integer>();

        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line;
            while ((line = br.readLine()) != null) {
                // process the line.
                int value = processLine(line);
                lineValues.add(value);
                sum += value;
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }    
        
        for (Integer i : lineValues) {
            System.out.println(i);
        }
        return sum;
    }

    public static int processLine(String line) {
        System.out.println("Processing line: " + line);
        int exponent = 0;
        // We want to remove the first part in the form of "Card X: ".
        line = line.split(": ")[1];

        // Now our string looks like "___ ___ ___ ___ ___ | ___ ___ ___ ...", and we'll split by " | ".
        String[] parts = line.split(" \\| ");
        
        ArrayList<String> keys = new ArrayList<String>();

        // We process the keys first.

        String[] keyParts = parts[0].split(" ");
        for (String keyPart : keyParts) {
            if (!keyPart.equals("")) keys.add(keyPart);
        }

        // Now we process the values.

        String[] valueParts = parts[1].split(" ");
        for (String valuePart : valueParts) {
            if (keys.contains(valuePart)) {
                System.out.println("Found: " + valuePart);
                // We've found a match!
                exponent++;
            }
        }

        if (exponent == 0) {
            return 0;
        } else {
            return (int) Math.pow(2, exponent - 1);
        }
    }

    public static int countMatches(String line) {
        int exponent = 0;
        // We want to remove the first part in the form of "Card X: ".
        line = line.split(": ")[1];

        // Now our string looks like "___ ___ ___ ___ ___ | ___ ___ ___ ...", and we'll split by " | ".
        String[] parts = line.split(" \\| ");
        
        ArrayList<String> keys = new ArrayList<String>();

        // We process the keys first.

        String[] keyParts = parts[0].split(" ");
        for (String keyPart : keyParts) {
            if (!keyPart.equals("")) keys.add(keyPart);
        }

        // Now we process the values.

        String[] valueParts = parts[1].split(" ");
        for (String valuePart : valueParts) {
            if (keys.contains(valuePart)) {
                // We've found a match!
                exponent++;
            }
        }

        return exponent;
    }

    // New file maybe? Add the same line a number of times equal to the number of matches?

    public static long countCards(String filename, int lines) {
        ArrayList<Long> counts = new ArrayList<Long>();
        try {
            int lineNumber = 0;
            BufferedReader br = new BufferedReader(new FileReader(filename));
            for (int i = 0; i < lines; i++) {
                counts.add((long) 1);
            }
            String line;
            while ((line = br.readLine()) != null) {
                // process the line.
                int count = countMatches(line);
                for (int i = lineNumber + 1; i < lineNumber + count + 1; i++) {
                    if (i < counts.size())
                        counts.set(i, counts.get(i) + counts.get(lineNumber));
                }
                lineNumber++;
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        long sum = 0;
        for (Long i : counts) {
            sum += i;
        }

        return sum;
    }

    public static void printArrayList(ArrayList<Long> list) {
        String output = "";
        for (Long i : list) {
            output += i + " ";
        }
        System.out.println(output);
    }



    public static void main(String[] args) {
        // Tried 168934, too high.
        //System.out.println(calculatePointTotal("day4_input.txt"));
        //System.out.println(calculatePointTotal("sample.txt"));
        System.out.println(countCards("day4_input.txt", 202));
        //System.out.println(countCards("sample.txt", 6));
    }
}



