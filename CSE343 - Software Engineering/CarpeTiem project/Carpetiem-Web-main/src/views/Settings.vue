<template>
  <body>
    <div id="nav-placeholder"></div>
    <div id="app">
      <form id="settings">
        <div class="for-name">
          <label for="usr_name">İsim: </label>
          <input v-model="userName" id="usr_name" placeholder="Yeni İsim" />
        </div>
        <br />
        <div class="for-pwd">
          <label for="usr_curr_pwd">Mevcut Şifre:</label>
          <input
            v-model="password"
            :type="is_pwd ? 'password' : 'text'"
            placeholder="Mevcut Şifre"
          />
        </div>

        <p id="error" style="color: #ad270a; margin-left: 40px"></p>

        <br />
        <div class="for-newPwd">
          <label for="usr_newpwd">Yeni Şifre:</label>
          <input
            v-model="new_pwd"
            :type="is_pwd ? 'password' : 'text'"
            placeholder="Yeni Şifre"
          />
        </div>
        <br />
        <div class="for-rePwd">
          <label for="usr_pwd_check">Tekrar Yeni Şifre:</label>
          <input
            v-model="re_pwd"
            :type="is_pwd ? 'password' : 'text'"
            placeholder="Tekrar Yeni Şifre"
          />
          <button
            @click="is_pwd = !is_pwd"
            type="button"
            :class="is_pwd ? 'bi-eye-slash' : 'bi-eye'"
            id="togglePassword"
          ></button>
        </div>
        <br />

        <p id="error2" style="color: #ad270a; margin-left: 40px"></p>
        <div class="for-email">
          <label for="usr_email">Email:</label>
          <input v-model="email" id="usr_email" placeholder="Yeni Email" />
        </div>
        <br />
        <div class="for-adress">
          <label for="usr_adress">Adres:</label>
          <input v-model="adress" id="usr_adress" placeholder="Yeni Adres" />
        </div>
        <br />
        <div class="for-phone">
          <label for="usr_phone">Tel. Numarası:</label>
          <input
            v-model="telNo"
            id="usr_phone"
            placeholder="Yeni Numara +90 "
            maxlength="14"
          />
        </div>
        <br />
        <div class="for-city">
          <label for="usr_city">Şehir:</label>
          <input v-model="city" id="usr_city" placeholder="Yeni Şehir " />
        </div>
        <br />
        <div class="for-district">
          <label for="usr_district">Semt:</label>
          <input
            v-model="district"
            id="usr_district"
            placeholder="Yeni Semt "
          />
        </div>
        <br />
        <div class="for-neighborhood">
          <label for="usr_neighborhood">Mahalle:</label>
          <input
            v-model="neighborhood"
            id="usr_neighborhood"
            placeholder="Yeni Mahalle"
          />
        </div>
        <br />
        <button
          @click="save"
          type="button"
          class="btn btn-secondary"
          style="background-color: #24252a"
        >
          Kaydet
        </button>
      </form>
    </div>
  </body>
</template>

<script>
import { ref } from "@vue/reactivity";
import firebase from "firebase/compat/app";
import "firebase/compat/auth";
import db from "../firebase";
export default {
  name: "App",
  setup() {
    const userName = ref("");
    const telNo = ref("");
    const email = ref("");
    const adress = ref("");
    const password = ref("");
    const new_pwd = ref("");
    const re_pwd = ref("");
    const city = ref("");
    const district = ref("");
    const neighborhood = ref("");
    const is_pwd = ref(true);
    firebase.auth().onAuthStateChanged(function (user) {
      if (user) {
        // User is signed in.
        db.collection("customers")
          .doc(firebase.auth().currentUser.uid)
          .get()
          .then((doc) => {
            if (doc.exists) {
              userName.value = doc.data().name;
              telNo.value = doc.data().phone;
              email.value = doc.data().email;
              adress.value = doc.data().address;
              city.value = doc.data().city;
              district.value = doc.data().district;
              neighborhood.value = doc.data().neighborhood;
            }
          });
      } else {
        console.log("USER GİRMEDİ");
      }
    });
    const save = () => {
      verify(password).then((result) => {
        if (result == false) {
          document.getElementById("error").innerHTML =
            "Geçersiz şifre. En az 6 karakter olmalı";
          return;
        } else {
          if (re_pwd.value == new_pwd.value && re_pwd.value != "") {
            password.value = re_pwd.value;

            var user = firebase.auth().currentUser;
            user
              .updatePassword(password.value)
              .then(() => {
                console.log("Password updated!");
              })
              .catch((error) => {
                console.log(error);
              });
          } else if (re_pwd.value == "") {
            db.collection("customers")
              .doc(firebase.auth().currentUser.uid)
              .update({
                name: userName.value,
                phone: telNo.value,
                email: email.value,
                address: adress.value,
                city: city.value,
                district: district.value,
                neighborhood: neighborhood.value,
              });
            user.updateEmail(email.value);
          } else {
            document.getElementById("error2").innerHTML = "Şifreler aynı değil";
          }
        }
        document.getElementById("error").innerHTML = "";
      });
    };
    const save_credential = () => {};
    function verify(providedPassword) {
      const user = firebase.auth().currentUser;
      var credential = firebase.auth.EmailAuthProvider.credential(
        user.email,
        providedPassword.value
      );

      return user
        .reauthenticateWithCredential(credential)
        .then(() => {
          // Signed in
          return true;
        })
        .catch((err) => {
          document.getElementById("error").innerHTML = "Invalid Password";
          return false;
        });
    }
    return {
      userName,
      telNo,
      email,
      adress,
      password,
      new_pwd,
      re_pwd,
      is_pwd,
      city,
      district,
      neighborhood,
      save,
      verify,
    };
  },
};
</script>

<style scoped>
form {
 
  padding: 9.5%;
  display: flex;
  flex-direction: column;
  align-items: center;
}
label {
  width: 100px;
  display: inline-block;
  text-align: center;
  vertical-align: middle;
}
.for-rePwd button {
  height: 25px;
  width: 25px;
  background-color: transparent;
  border-style: solid;
  border: none;
  margin-left: -25px;
}
</style>
