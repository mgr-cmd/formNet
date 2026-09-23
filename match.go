package main

import (
	"encoding/csv"
	"fmt"
	"log"
	"os"
	"strconv"
	"time"
)

type Match struct {
	ID        int
	HomeTeam  string
	AwayTeam  string
	HomeGoals int
	AwayGoals int
	Date      string
}

// getting the last5 matches

func getLast5Matches(teamName string, beforeDate string, allMatches []Match) []Match {

	var result []Match
	// parsing the cutoff date, which is in string, so parsing helps to make reasoning with it

	bdate, _ := time.Parse("02/01/2006", beforeDate)
	// we are looping from backwards coz we want the last5 or the latest5 before the cutoff date
	// if we looped from front then we would be looping all the matches that happened before the cutoff date
	// we just want the latest 5 matches before the cutoff date
	// kinda mind boggling at this point
	// but it is pretty good
	for i := len(allMatches) - 1; i >= 0; i-- {

		m := allMatches[i]

		mdate, _ := time.Parse("02/01/2006", m.Date)

		if (m.HomeTeam == teamName || m.AwayTeam == teamName) && mdate.Before(bdate) {

			result = append(result, m)
		}

		if len(result) == 5 {

			break
		}

	}

	return result

}

// a slice of computation which holds avgData:  avgGoalsConceded, pointsPerGame, winRate

type Form struct {
	AvgGoalsScored   float64
	AvgGoalsConceded float64
	WinRate          float64
	PointsPerGame    float64
}

// computation

func computeForm(matches []Match, teamName string) (data Form) {

	goalsScored := 0
	goalsConceded := 0
	wins := 0
	points := 0

	for i := 0; i < len(matches); i++ {
		m := matches[i]
		if m.HomeTeam == teamName {

			goalsScored += m.HomeGoals
			goalsConceded += m.AwayGoals

			if m.HomeGoals > m.AwayGoals {

				wins++
				points += 3

			} else if m.HomeGoals == m.AwayGoals {

				points += 1

			}

		} else if m.AwayTeam == teamName {

			goalsScored += m.AwayGoals
			goalsConceded += m.HomeGoals

			if m.AwayGoals > m.HomeGoals {

				wins++
				points += 3

			} else if m.AwayGoals == m.HomeGoals {

				points += 1

			}

		}

	}

	// computing averages

	matchesPlayed := float64(len(matches))
	avgData := Form{

		AvgGoalsScored:   float64(goalsScored) / matchesPlayed,
		AvgGoalsConceded: float64(goalsConceded) / matchesPlayed,
		WinRate:          float64(wins) / matchesPlayed,
		PointsPerGame:    float64(points) / matchesPlayed,
	}
	return avgData

}

func main() {

	// opening a csv encoded file

	file, err := os.Open("./epl_23_24.csv") // for read access
	if err != nil {
		log.Fatal(err)

	}
	defer file.Close() // making sure the file closes

	// reading the csv file

	reader := csv.NewReader(file)
	records, err := reader.ReadAll()
	if err != nil {

		log.Fatal(err)

	}

	// creating a new Matches []Match, all the records from the csv

	var matches []Match
	for i := 1; i < len(records); i++ {
		fthg, _ := strconv.Atoi(records[i][5])
		ftag, _ := strconv.Atoi(records[i][6])
		m := Match{ID: i, // matches is the name of the slice, each index represents one match which has all these fields
			HomeTeam:  records[i][3],
			AwayTeam:  records[i][4],
			HomeGoals: fthg,
			AwayGoals: ftag,
			Date:      records[i][1],
		}
		matches = append(matches, m)
	}

	fmt.Println("\n----	 EPL 2023/2024		----\n")

	/** reading directly from the records
	for i := 1; i <= 6; i++ {

		date := records[i][1]
		home := records[i][3]
		away := records[i][4]
		fthg, _ := strconv.Atoi(records[i][5])
		ftag, _ := strconv.Atoi(records[i][6])

		fmt.Printf("%s | %s %d-%d %s 	\n", date, home,
			fthg, ftag, away)

	} **/

	// reading from the matches[]

	last5 := getLast5Matches("Arsenal", "01/01/2024", matches)
	fmt.Println("\n------ Last 5 Matches Arsenal before 1 Jan 2024----\n")
	for i := 0; i < len(last5); i++ {
		m := last5[i]
		fmt.Printf("%s	%s %d-%d %s \n", m.Date, m.HomeTeam, m.HomeGoals, m.AwayGoals, m.AwayTeam)

	}
	// computing last5avg
	avgData := computeForm(last5, "Arsenal")

	fmt.Printf("\n------ Arsenal Last 5 Avg Data ------------  \n\n")
	fmt.Printf("Average Score: %f\n", avgData.AvgGoalsScored)
	fmt.Printf("Average Goals Conceded: %f\n", avgData.AvgGoalsConcededi)
	fmt.Printf("Win Rate : %f\n", avgData.WinRate)
	fmt.Printf("Avg Points: %f\n", avgData.PointsPerGame)

	/** for i := 0; i < 5; i++ {

		m := last5[i]
		fmt.Printf("%s | %s %d-%d %s    \n", m.Date, m.HomeTeam,
			m.HomeGoals, m.AwayGoals, m.AwayTeam)

	} **/

	fmt.Printf("Loaded :%d\n", len(matches))

}
