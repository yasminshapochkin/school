import { Exam } from "../models/Exam.js";
import { Question } from "../models/Question.js";

export class ExamService {
    constructor() {
        this.storageKey = "exams";
    }

    getAllExams() {
        //.. עקא גשאש כרםצ ךםבשך דאםרשעק נט קסשצד לקט
        // et data from losal storage by examms key 
        const data = localStorage.getItem(this.storageKey);

        if (!data) {
            return [];
        }
        // continuew if  key exists and parse data to array of ogjects 
        const plainExams = JSON.parse(data);
        // map is 
        // for each examData(Exam) return new Exam object with the same for eatch 
        // QuestionData(Question) in examData.questions return new Question
        //clone the data to new objects to avoiddirect manipulation of 

        let allExamsClones = plainExams.map(examData => {
            const exam = new Exam(examData.title);

            exam.id = examData.id;
            exam.createdAt = examData.createdAt;
            // inner clone for Questions
            exam.questions = examData.questions.map(questionData => {
                const question = new Question(
                    questionData.text,
                    questionData.answers,
                    questionData.correctAnswerIndex
                );

                question.id = questionData.id;

                return question;
            });

            return exam;
        });
        return allExamsClones;
    }

    //save to local storage
    saveExam(exam) {
        // get a clone of all exams
        const exams = this.getAllExams();
        // delet this one if it already exists
        // deleteExam(exam.id);

        // add the exam
        exams.push(exam);
        // return to local storage
        localStorage.setItem(this.storageKey, JSON.stringify(exams));
    }

    deleteExam(examId) {
        const exams = this.getAllExams();

        const filteredExams = exams.filter(exam => exam.id !== examId);

        localStorage.setItem(this.storageKey, JSON.stringify(filteredExams));
    }

    getExamById(examId) {
        const exams = this.getAllExams();

        return exams.find(exam => exam.id === examId);
    }

    clearAllExams() {
        localStorage.removeItem(this.storageKey);
    }
}