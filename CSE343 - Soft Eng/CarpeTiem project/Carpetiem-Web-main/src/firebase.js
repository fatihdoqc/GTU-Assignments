import firebase from "firebase/compat/app";
import "firebase/compat/firestore";
import "firebase/compat/auth";
import "firebase/compat/storage";
import "firebase/compat/functions";

const firebaseConfig = {
  apiKey: "AIzaSyBiZ0W8druRY1pr5FPOoCFwlk3H2w_pL6o",
  authDomain: "hali-4cdae.firebaseapp.com",
  databaseURL:
    "https://hali-4cdae-default-rtdb.europe-west1.firebasedatabase.app",
  projectId: "hali-4cdae",
  storageBucket: "hali-4cdae.appspot.com",
  messagingSenderId: "22371174264",
  appId: "1:22371174264:web:94a42bb5dd637fcb226a8d",
  measurementId: "G-EFLR7VGFMK",
};

const firebaseApp = firebase.initializeApp(firebaseConfig);
export const timestamp = firebase.firestore.FieldValue.serverTimestamp;
export const storage = firebaseApp.storage();
export const functions = firebaseApp.functions("europe-west1");
export const auth = firebase.auth();
export const persistence = firebase.auth.Auth.Persistence;
const db = firebaseApp.firestore();
export default db;
