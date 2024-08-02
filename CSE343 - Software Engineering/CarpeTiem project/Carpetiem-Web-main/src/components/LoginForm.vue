<template>
  <h4 class="text-center mb-3">{{ header }}</h4>
  <form novalidate>
    <div class="row mb-3">
      <div class="col-md-12">
        <label for="email" class="form-label">Email</label>
        <div class="input-group has-validation">
          <span class="input-group-text">
            <i class="bi bi-envelope-fill"></i>
          </span>
          <input
            :id="user_type + '-email'"
            type="email"
            class="form-control"
            :placeholder="placeholder"
            autocomplete="off"
            v-model="email"
            @keyup="
              is_email_valid = /^([a-z][a-z0-9_-]*@[a-z]+\.[a-z]+)$/.test(email)
            "
            :class="{
              '': is_email_valid === '',
              'is-valid': is_email_valid,
              'is-invalid': is_email_valid === false,
            }"
            required
          />
          <div class="invalid-feedback">
            Lütfen geçerli bir email adresi giriniz
          </div>
        </div>
      </div>
    </div>
    <div class="row mb-3">
      <div class="col-md-12">
        <label for="password" class="form-label">Şifre</label>
        <div class="input-group has-validation">
          <span class="input-group-text">
            <i class="bi bi-lock-fill"></i>
          </span>
          <input
            :id="user_type + '-password'"
            :type="is_pwd ? 'password' : 'text'"
            class="form-control shadow-end-0 border-end-0"
            autocomplete="off"
            v-model="password"
            @keyup="is_pwd_valid = password.length >= 6"
            :class="{
              '': is_pwd_valid === '',
              'is-valid': is_pwd_valid,
              'is-invalid': is_pwd_valid === false,
            }"
            required
          />
          <span
            class="input-group-text bg-white"
            @click="is_pwd = !is_pwd"
            :class="{
              '': is_pwd_valid === '',
              'border-success': is_pwd_valid,
              'border-danger': is_pwd_valid === false,
            }"
          >
            <i
              class="bi"
              :class="{ 'bi-eye-slash': is_pwd, 'bi-eye': !is_pwd }"
            ></i>
          </span>
          <div class="invalid-feedback">
            Şifreniz en az 6 karakter olmalıdır
          </div>
        </div>
      </div>
    </div>
    <div
      class="alert alert-danger d-flex align-items-center alert-dismissible"
      role="alert"
      v-if="error"
    >
      <i class="bi bi-exclamation-triangle-fill me-2"></i>
      <div>Kullanıcı adı yada şifre hatalı</div>
      <button
        type="button"
        class="btn-close"
        data-hide="alert"
        aria-label="Close"
        @click="error = false"
      ></button>
    </div>
    <div class="row justify-content-between mb-2">
      <div class="col-md-auto">
        <div class="form-check">
          <input
            class="form-check-input"
            type="checkbox"
            value=""
            :id="user_type + 'always-login'"
            v-model="always_login"
          />
          <label class="form-check-label" :for="user_type + 'always-login'">
            Beni hatırla
          </label>
        </div>
      </div>
      <div class="col-md-auto">
        <router-link to="#" style="text-decoration: none">
          Şifrenizi mi unuttunuz <i class="bi bi-box-arrow-up-right"></i>
        </router-link>
      </div>
    </div>
    <div class="row mb-2">
      <div class="d-grid">
        <button
          class="btn"
          type="button"
          :disabled="!is_pwd_valid || !is_email_valid"
          @click="login"
        >
          Giriş
        </button>
      </div>
    </div>

    <div class="row">
      <div class="col-auto mx-auto">
        Hesabınız yok mu?
        <router-link
          :to="{ name: user_type == 'firm' ? 'FirmRegister' : 'Register' }"
          style="text-decoration: none"
        >
          Şimdi oluşturun <i class="bi bi-box-arrow-up-right"></i>
        </router-link>
      </div>
    </div>

    <div class="row" v-if="user_type != 'firm'">
      <div class="col-auto mx-auto">
        Firmanız mı var?
        <router-link :to="{ name: 'AdminLogin' }" style="text-decoration: none">
          Buradan giriş yapın <i class="bi bi-box-arrow-up-right"></i>
        </router-link>
      </div>
    </div>
  </form>
</template>

<script>
import { ref } from "@vue/reactivity";
import { useRouter } from "vue-router";
import { functions, auth, persistence } from "../firebase";
export default {
  name: "LoginForm",
  props: {
    header: String,
    placeholder: String,
    user_type: String,
  },
  setup(props) {
    const email = ref("");
    const password = ref("");
    const is_email_valid = ref("");
    const is_pwd_valid = ref("");
    const error = ref(false);
    const is_pwd = ref(true);
    const router = useRouter();
    const always_login = ref(false);

    const login = async () => {
      try {
        const getUserByEmail = functions.httpsCallable("getUserByEmail");
        const userInfo = (await getUserByEmail({ email: email.value })).data;
        if (props.user_type == userInfo.displayName) {
          try {
            await auth.signInWithEmailAndPassword(email.value, password.value);
            if (always_login.value) {
              auth.setPersistence(persistence.LOCAL);
            } else {
              auth.setPersistence(persistence.SESSION);
            }
            router.replace("/");
          } catch (error) {
            throw error;
          }
        } else {
          throw { message: "not in collection " + props.user_type };
        }
      } catch (err) {
        console.log(err.message);
        error.value = true;
        email.value = "";
        password.value = "";
        is_email_valid.value = "";
        is_pwd_valid.value = "";
      }
      /*db.collection(props.user_type + "s")
        .where("email", "==", email.value)
        .get()
        .then((snap) => {
          if (snap.size == 0) {
            throw "not in collection";
          } else {
            return auth
              .signInWithEmailAndPassword(email.value, password.value);
          }
        })
        .then((user) => {
          if (always_login.value) {
            auth
              .setPersistence(persistence.LOCAL);
          } else {
            auth
              .setPersistence(persistence.SESSION);
          }
          router.replace("/");
        })
        .catch((err) => {
          console.log(err, props.user_type);
          error.value = true;
          email.value = "";
          password.value = "";
          is_email_valid.value = "";
          is_pwd_valid.value = "";
        });*/
    };

    return {
      email,
      password,
      is_email_valid,
      is_pwd_valid,
      login,
      error,
      is_pwd,
      always_login,
    };
  },
};
</script>

<style scoped>
.btn {
  background-color: rgb(120, 150, 120);
  border: rgb(120, 150, 120);
}

.btn:hover {
  filter: brightness(85%);
}
</style>

<style>
.form-check-input:checked {
  background-color: rgb(120, 150, 120);
  border-color: rgb(120, 150, 120);
}

.form-check-input:focus {
  border-color: rgb(120, 150, 120);
}
</style>
