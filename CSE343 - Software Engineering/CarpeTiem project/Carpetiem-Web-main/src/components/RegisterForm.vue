<template>
  <h4 class="text-center mb-3">{{ header }}</h4>
  <form novalidate>
    <div class="row g-2">
      <div class="col-md-12">
        <label :for="user_type + '-name'" class="form-label">
          <span style="color: red">*</span> İsim
        </label>
        <div class="input-group has-validation">
          <input
            v-model="name"
            type="text"
            class="form-control"
            :id="user_type + '-name'"
            autocomplete="off"
            @keyup="is_name_valid = name.length != 0"
            :class="{
              '': is_name_valid === '',
              'is-valid': is_name_valid,
              'is-invalid': is_name_valid === false,
            }"
          />
          <div class="invalid-feedback">Lütfen bir isim giriniz</div>
        </div>
      </div>
      <div class="col-md-12">
        <label :for="user_type + '-phone'" class="form-label">
          <span style="color: red">*</span> Telefon Numarası
        </label>
        <div class="input-group has-validation">
          <input
            v-model="phone"
            type="tel"
            class="form-control"
            autocomplete="off"
            maxlength="14"
            :id="user_type + '-phone'"
            @keydown="enforceFormat"
            @keyup="
              formatToPhone($event);
              is_phone_valid = phone.length == 14;
            "
            :class="{
              '': is_phone_valid === '',
              'is-valid': is_phone_valid,
              'is-invalid': is_phone_valid === false,
            }"
          />
          <div class="invalid-feedback">
            Lütfen geçerli bir telefon numarası giriniz
          </div>
        </div>
      </div>
      <div class="col-md-12">
        <label :for="user_type + '-email'" class="form-label">
          <span style="color: red">*</span> Email
        </label>
        <div class="input-group has-validation">
          <input
            v-model="email"
            type="email"
            class="form-control"
            :id="user_type + '-email'"
            autocomplete="off"
            placeholder="example@example.com"
            @keyup="
              is_email_valid = /^([a-z][a-z0-9_-]*@[a-z]+\.[a-z]+)$/.test(email)
            "
            :class="{
              '': is_email_valid === '',
              'is-valid': is_email_valid,
              'is-invalid': is_email_valid === false,
            }"
          />
          <div class="invalid-feedback">
            Lütfen geçerli bir email adresi giriniz
          </div>
        </div>
      </div>
      <div class="col-md-12">
        <label :for="user_type + '-password'" class="form-label">
          <span style="color: red">*</span> Şifre
        </label>
        <div class="input-group has-validation">
          <input
            v-model="pwd"
            :type="is_pwd ? 'password' : 'text'"
            class="form-control border-end-0"
            :id="user_type + '-password'"
            autocomplete="off"
            @keyup="is_pwd_valid = pwd.length >= 6"
            :class="{
              '': is_pwd_valid === '',
              'is-valid': is_pwd_valid,
              'is-invalid': is_pwd_valid === false,
            }"
          />
          <span
            class="input-group-text bg-transparent"
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
      <div class="col-md-6">
        <label :for="user_type + '-city-select'" class="form-label">
          <span style="color: red">*</span> İl
        </label>
        <div class="input-group has-validation">
          <select
            class="form-select"
            v-model="city"
            @change="onCityChange"
            :id="user_type + '-city-select'"
            :class="{
              '': is_city_valid === '',
              'is-valid': is_city_valid,
              'is-invalid': is_city_valid === false,
            }"
          >
            <option value="default">İlinizi seçiniz</option>
            <option v-for="city in cities" :key="city" :value="city">
              {{ city }}
            </option>
          </select>
          <div class="invalid-feedback">Lütfen bir il seçiniz</div>
        </div>
      </div>
      <div class="col-md-6">
        <label :for="user_type + '-district-select'" class="form-label">
          <span style="color: red">*</span> İlçe
        </label>
        <div class="input-group has-validation">
          <select
            class="form-select"
            v-model="dist"
            @change="onDistrictChange"
            :disabled="!is_city_valid"
            :id="user_type + '-district-select'"
            :class="{
              '': is_dist_valid === '',
              'is-valid': is_dist_valid,
              'is-invalid': is_dist_valid === false,
            }"
          >
            <option value="default">İlçenizi seçiniz</option>
            <option
              v-for="district in districts"
              :key="district"
              :value="district"
            >
              {{ district }}
            </option>
          </select>
          <div class="invalid-feedback">Lütfen bir ilçe seçiniz</div>
        </div>
      </div>
      <div class="col-md-12">
        <label :for="user_type + '-neighborhood-select'" class="form-label">
          <span style="color: red">*</span> Semt
        </label>
        <div class="input-group has-validation">
          <select
            class="form-select"
            v-model="nbhd"
            :disabled="!is_dist_valid || !is_city_valid"
            :id="user_type + '-neighborhood-select'"
            @change="is_nbhd_valid = nbhd != 'default'"
            :class="{
              '': is_nbhd_valid === '',
              'is-valid': is_nbhd_valid,
              'is-invalid': is_nbhd_valid === false,
            }"
          >
            <option value="default">Semtinizi seçiniz</option>
            <option
              v-for="neighborhood in neighborhoods"
              :key="neighborhood"
              :value="neighborhood"
            >
              {{ neighborhood }}
            </option>
          </select>
          <div class="invalid-feedback">Lütfen bir semt seçiniz</div>
        </div>
      </div>
      <div class="col-md-12">
        <label :for="user_type + '-address'" class="form-label">
          <span style="color: red">*</span> Adres
        </label>
        <div class="input-group has-validation">
          <textarea
            v-model="addr"
            class="form-control"
            :id="user_type + '-address'"
            rows="2"
            style="resize: none"
            autocomplete="off"
            @keyup="is_addr_valid = addr.length != 0"
            :class="{
              '': is_addr_valid === '',
              'is-valid': is_addr_valid,
              'is-invalid': is_addr_valid === false,
            }"
          ></textarea>
          <div class="invalid-feedback">Lütfen bir adres giriniz</div>
        </div>
      </div>
      <div
        class="alert alert-danger d-flex align-items-center alert-dismissible"
        role="alert"
        v-if="error"
      >
        <i class="bi bi-exclamation-triangle-fill me-2"></i>
        <div class="text-wrap">
          Bu e-posta başka bir kullanıcı tarafından kullanılmaktadır. Lütfen
          başka bir e-posta girin
        </div>
        <button
          type="button"
          class="btn-close"
          data-hide="alert"
          aria-label="Close"
          @click="error = false"
        ></button>
      </div>
      <div class="d-grid col-md-12 mx-auto mb-2">
        <button
          class="btn"
          @click="user_type != 'employee' ? register() : employeeRegister()"
          type="button"
          :disabled="
            !is_city_valid ||
            !is_dist_valid ||
            !is_nbhd_valid ||
            !is_name_valid ||
            !is_phone_valid ||
            !is_email_valid ||
            !is_pwd_valid ||
            !is_addr_valid
          "
        >
          Kaydol
        </button>
      </div>
      <div class="col-md-auto mx-auto" v-if="user_type != 'employee'">
        Hesabınız var mı?
        <router-link
          :to="{ name: user_type == 'firm' ? 'AdminLogin' : 'Login' }"
          style="text-decoration: none"
        >
          Giriş yapın <i class="bi bi-box-arrow-up-right"></i>
        </router-link>
      </div>
      <div class="row">
        <div class="col-md-auto mx-auto" v-if="user_type == 'customer'">
          Firmanız mı var?
          <router-link
            :to="{ name: 'FirmRegister' }"
            style="text-decoration: none"
          >
            Buradan kaydolun <i class="bi bi-box-arrow-up-right"></i>
          </router-link>
        </div>
      </div>
    </div>
  </form>
</template>

<script>
import { ref } from "@vue/reactivity";
import db, { storage, auth, functions } from "../firebase";
import { useRouter } from "vue-router";
import { registered } from "../App.vue";
export default {
  name: "RegisterForm",
  props: {
    header: String,
    user_type: String,
  },
  emits: ["closePopUp", "openAdditional"],
  setup(props, { emit }) {
    const city = ref("default");
    const dist = ref("default");
    const nbhd = ref("default");
    const name = ref("");
    const phone = ref("");
    const email = ref("");
    const pwd = ref("");
    const firmId = ref("");
    const addr = ref("");
    const cities = ref([]);
    const districts = ref([]);
    const neighborhoods = ref([]);
    const is_city_valid = ref("");
    const is_dist_valid = ref("");
    const is_nbhd_valid = ref("");
    const is_name_valid = ref("");
    const is_phone_valid = ref("");
    const is_email_valid = ref("");
    const is_pwd_valid = ref("");
    const is_addr_valid = ref("");
    const is_pwd = ref(true);
    const error = ref(false);
    const router = useRouter();

    db.collection("cities")
      .get()
      .then((snap) => {
        snap.forEach((doc) => {
          cities.value.push(doc.data().name);
        });
        cities.value.sort(new Intl.Collator("de").compare);
      });

    const onCityChange = async () => {
      districts.value = [];

      let snap = await db
        .collection("cities")
        .where("name", "==", city.value)
        .get();

      snap.forEach((doc) => {
        doc.data().districts.forEach((district) => {
          districts.value.push(district.name);
        });
      });

      districts.value.sort(new Intl.Collator("de").compare);
      dist.value = "default";
      nbhd.value = "default";
      is_dist_valid.value = null;
      is_nbhd_valid.value = null;
      is_city_valid.value = city.value != "default";
    };

    const onDistrictChange = async () => {
      neighborhoods.value = [];

      let snap = await db
        .collection("cities")
        .where("name", "==", city.value)
        .get();

      snap.forEach((doc) => {
        doc.data().districts.some((district) => {
          if (district.name === dist.value) {
            district.neighborhoods.forEach((neighborhood) => {
              neighborhoods.value.push(neighborhood);
            });
            return true;
          }
        });
      });

      neighborhoods.value.sort(new Intl.Collator("de").compare);
      nbhd.value = "default";
      is_nbhd_valid.value = null;
      is_dist_valid.value = dist.value != "default";
    };

    const isNumericInput = (event) => {
      const key = event.keyCode;
      return (
        (key >= 48 && key <= 57) || // Allow number line
        (key >= 96 && key <= 105) // Allow number pad
      );
    };

    const isModifierKey = (event) => {
      const key = event.keyCode;
      return (
        event.shiftKey === true ||
        key === 35 ||
        key === 36 || // Allow Shift, Home, End
        key === 8 ||
        key === 9 ||
        key === 13 ||
        key === 46 || // Allow Backspace, Tab, Enter, Delete
        (key > 36 && key < 41) || // Allow left, up, right, down
        // Allow Ctrl/Command + A,C,V,X,Z
        ((event.ctrlKey === true || event.metaKey === true) &&
          (key === 65 || key === 67 || key === 86 || key === 88 || key === 90))
      );
    };

    const enforceFormat = (event) => {
      // Input must be of a valid number format or a modifier key, and not longer than ten digits
      if (!isNumericInput(event) && !isModifierKey(event)) {
        event.preventDefault();
      }
    };

    const formatToPhone = (event) => {
      if (isModifierKey(event)) {
        if (event.keyCode == 8) {
          is_phone_valid.value = false;
        }
        return;
      }

      const input = event.target.value.replace(/\D/g, "").substring(0, 10); // First ten digits of input only
      const areaCode = input.substring(0, 3);
      const middle = input.substring(3, 6);
      const last = input.substring(6, 10);

      is_phone_valid.value = input.length == 10 ? true : false;

      if (input.length > 6) {
        event.target.value = `(${areaCode}) ${middle} ${last}`;
      } else if (input.length > 3) {
        event.target.value = `(${areaCode}) ${middle}`;
      } else if (input.length > 0) {
        event.target.value = `(${areaCode}`;
      }
    };

    const register = () => {
      registered(props.user_type);
      auth
        .createUserWithEmailAndPassword(email.value, pwd.value)
        .then(async (cred) => {
          db.collection(props.user_type + "s")
            .doc(cred.user.uid)
            .set({
              name: name.value,
              phone: phone.value,
              address: addr.value,
              city: city.value,
              district: dist.value,
              neighborhood: nbhd.value,
            });

          cred.user.updateProfile({
            displayName: props.user_type,
          });

          if (props.user_type == "firm") {
            var notFoundImg = await storage
              .ref()
              .child("ImageNotFound.png")
              .getDownloadURL();
            cred.user.updateProfile({
              photoURL: notFoundImg.toString(),
            });
          }
          registered("none");
          if (props.user_type == "firm") {
            emit("openAdditional");
          } else {
            router.replace("/");
          }
        })
        .catch((err) => {
          error.value = true;
          email.value = "";
          is_email_valid.value = "";
          registered("none");
        });
    };

    const employeeRegister = async () => {
      try {
        console.log(addr.value);
        const createUser = functions.httpsCallable("createUser");
        createUser({
          name: name.value,
          phone: phone.value,
          email: email.value,
          password: pwd.value,
          address: addr.value,
          city: city.value,
          district: dist.value,
          neighborhood: nbhd.value,
          //firmId:
        }).then((user) => {
          console.log(user.data);
        });
        emit("closePopUp");
      } catch {
        error.value = true;
        email.value = "";
        is_email_valid.value = "";
      }
    };

    return {
      city,
      dist,
      nbhd,
      name,
      phone,
      email,
      pwd,
      addr,
      cities,
      districts,
      neighborhoods,
      is_city_valid,
      is_dist_valid,
      is_nbhd_valid,
      is_name_valid,
      is_phone_valid,
      is_email_valid,
      is_pwd_valid,
      is_addr_valid,
      is_pwd,
      onCityChange,
      onDistrictChange,
      enforceFormat,
      formatToPhone,
      register,
      error,
      employeeRegister,
      firmId,
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

.btn:focus {
  box-shadow: 0 0 0 0.25rem rgb(120 150 120 / 25%);
}
</style>
