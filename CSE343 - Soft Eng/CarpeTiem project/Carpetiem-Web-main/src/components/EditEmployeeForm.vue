<template>
  <form novalidate>
    <div class="row g-2">
      <div class="col-md-12">
        <label :for="'employee-edit' + '-name'" class="form-label">
          <span style="color: red">*</span> Name
        </label>
        <div class="input-group has-validation">
          <input
            v-model="name"
            type="text"
            class="form-control"
            :id="'employee-edit' + '-name'"
            autocomplete="off"
            @keyup="is_name_valid = name.length != 0"
            :class="{
              'is-valid': is_name_valid,
              'is-invalid': is_name_valid === false,
            }"
          />
          <div class="invalid-feedback">Name is required</div>
        </div>
      </div>
      <div class="col-md-12">
        <label :for="'employee-edit' + '-phone'" class="form-label">
          <span style="color: red">*</span> Phone Number
        </label>
        <div class="input-group has-validation">
          <input
            v-model="phone"
            type="tel"
            class="form-control"
            autocomplete="off"
            maxlength="14"
            :id="'employee-edit' + '-phone'"
            @keydown="enforceFormat"
            @keyup="
              formatToPhone($event);
              is_phone_valid = phone.length == 14;
            "
            :class="{
              'is-valid': is_phone_valid,
              'is-invalid': is_phone_valid === false,
            }"
          />
          <div class="invalid-feedback">Valid phone number is required</div>
        </div>
      </div>
      <div class="col-md-12">
        <label :for="'employee-edit' + '-email'" class="form-label">
          <span style="color: red">*</span> Email
        </label>
        <div class="input-group has-validation">
          <input
            v-model="email"
            type="email"
            class="form-control"
            :id="'employee-edit' + '-email'"
            autocomplete="off"
            placeholder="example@example.com"
            @keyup="
              is_email_valid = /^([a-z][a-z0-9_-]*@[a-z]+\.[a-z]+)$/.test(email)
            "
            :class="{
              'is-valid': is_email_valid,
              'is-invalid': is_email_valid === false,
            }"
          />
          <div class="invalid-feedback">Valid email is required</div>
        </div>
      </div>
      <div class="col-md-12">
        <label :for="'employee-edit' + '-password'" class="form-label">
          <span style="color: red">*</span> Password
        </label>
        <div class="input-group has-validation">
          <input
            v-model="pwd"
            :type="is_pwd ? 'password' : 'text'"
            class="form-control border-end-0"
            :id="'employee-edit' + '-password'"
            autocomplete="off"
            @keyup="is_pwd_valid = pwd.length >= 6"
            :class="{
              'is-valid': is_pwd_valid,
              'is-invalid': is_pwd_valid === false,
            }"
          />
          <span
            class="input-group-text bg-transparent"
            @click="is_pwd = !is_pwd"
            :class="{
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
            Password must be at least 6 characters long
          </div>
        </div>
      </div>
      <div class="col-md-6">
        <label :for="'employee-edit' + '-city-select'" class="form-label">
          <span style="color: red">*</span> City
        </label>
        <div class="input-group has-validation">
          <select
            class="form-select"
            v-model="city"
            @change="onCityChange"
            :id="'employee-edit' + '-city-select'"
            :class="{
              'is-valid': is_city_valid,
              'is-invalid': is_city_valid === false,
            }"
          >
            <option value="default">Select your city</option>
            <option v-for="city in cities" :key="city" :value="city">
              {{ city }}
            </option>
          </select>
          <div class="invalid-feedback">City is required</div>
        </div>
      </div>
      <div class="col-md-6">
        <label :for="'employee-edit' + '-district-select'" class="form-label">
          <span style="color: red">*</span> District
        </label>
        <div class="input-group has-validation">
          <select
            class="form-select"
            v-model="dist"
            @change="onDistrictChange"
            :disabled="!is_city_valid"
            :id="'employee-edit' + '-district-select'"
            :class="{
              'is-valid': is_dist_valid,
              'is-invalid': is_dist_valid === false,
            }"
          >
            <option value="default">Select your district</option>
            <option
              v-for="district in districts"
              :key="district"
              :value="district"
            >
              {{ district }}
            </option>
          </select>
          <div class="invalid-feedback">District is required</div>
        </div>
      </div>
      <div class="col-md-12">
        <label
          :for="'employee-edit' + '-neighborhood-select'"
          class="form-label"
        >
          <span style="color: red">*</span> Neighborhood
        </label>
        <div class="input-group has-validation">
          <select
            class="form-select"
            v-model="nbhd"
            :disabled="!is_dist_valid || !is_city_valid"
            :id="'employee-edit' + '-neighborhood-select'"
            @change="is_nbhd_valid = nbhd != 'default'"
            :class="{
              'is-valid': is_nbhd_valid,
              'is-invalid': is_nbhd_valid === false,
            }"
          >
            <option value="default">Select your neighborhood</option>
            <option
              v-for="neighborhood in neighborhoods"
              :key="neighborhood"
              :value="neighborhood"
            >
              {{ neighborhood }}
            </option>
          </select>
          <div class="invalid-feedback">Neighborhood is required</div>
        </div>
      </div>
      <div class="col-md-12">
        <label :for="'employee-edit' + '-address'" class="form-label">
          <span style="color: red">*</span> Address
        </label>
        <div class="input-group has-validation">
          <textarea
            v-model="addr"
            class="form-control"
            :id="'employee-edit' + '-address'"
            rows="2"
            style="resize: none"
            autocomplete="off"
            @keyup="is_addr_valid = addr.length != 0"
            :class="{
              'is-valid': is_addr_valid,
              'is-invalid': is_addr_valid === false,
            }"
          ></textarea>
          <div class="invalid-feedback">Address is required</div>
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
      <div class="d-grid col-md-12 mx-auto mb-4">
        <button
          class="btn btn-primary"
          @click="edit"
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
          Save
        </button>
      </div>
    </div>
  </form>
</template>

<script>
import { ref } from "@vue/reactivity";
import db, { functions } from "../firebase";
import "firebase/compat/auth";
import { watch } from "@vue/runtime-core";

export default {
  name: "EditEmployeeForm",
  props: {
    employee: Object,
  },
  emits: ["closePopUp"],
  setup(props, { emit }) {
    const city = ref(props.employee.city);
    const dist = ref(props.employee.district);
    const nbhd = ref(props.employee.neighborhood);
    const name = ref(props.employee.name);
    const phone = ref(props.employee.phone);
    const email = ref(props.employee.email);
    const pwd = ref(props.employee.password);
    const addr = ref(props.employee.address);
    const cities = ref([]);
    const districts = ref([]);
    const neighborhoods = ref([]);
    const is_city_valid = ref(true);
    const is_dist_valid = ref(true);
    const is_nbhd_valid = ref(true);
    const is_name_valid = ref(true);
    const is_phone_valid = ref(true);
    const is_email_valid = ref(true);
    const is_pwd_valid = ref(true);
    const is_addr_valid = ref(true);
    const is_pwd = ref(true);
    const error = ref(false);

    db.collection("cities")
      .get()
      .then((snap) => {
        snap.forEach((doc) => {
          cities.value.push(doc.data().name);
        });
        cities.value.sort(new Intl.Collator("de").compare);
      });

    db.collection("cities")
      .where("name", "==", city.value)
      .get()
      .then((snap) => {
        snap.forEach((doc) => {
          doc.data().districts.forEach((district) => {
            districts.value.push(district.name);
          });
        });
        districts.value.sort(new Intl.Collator("de").compare);
      });

    db.collection("cities")
      .where("name", "==", city.value)
      .get()
      .then((snap) => {
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
        districts.value.sort(new Intl.Collator("de").compare);
      });

    watch(
      () => props.employee,
      (newEmployee) => {
        city.value = newEmployee.city;
        dist.value = newEmployee.district;
        nbhd.value = newEmployee.neighborhood;
        name.value = newEmployee.name;
        phone.value = newEmployee.phone;
        email.value = newEmployee.email;
        addr.value = newEmployee.address;
        db.collection("cities")
          .get()
          .then((snap) => {
            snap.forEach((doc) => {
              cities.value.push(doc.data().name);
            });
            cities.value.sort(new Intl.Collator("de").compare);
          });

        db.collection("cities")
          .where("name", "==", city.value)
          .get()
          .then((snap) => {
            snap.forEach((doc) => {
              doc.data().districts.forEach((district) => {
                districts.value.push(district.name);
              });
            });
            districts.value.sort(new Intl.Collator("de").compare);
          });

        db.collection("cities")
          .where("name", "==", city.value)
          .get()
          .then((snap) => {
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
            districts.value.sort(new Intl.Collator("de").compare);
          });
      }
    );

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

    const edit = async () => {
      try {
        /*var cred = await secondaryApp
          .auth()
          .signInWithEmailAndPassword(
            props.employee.email,
            props.employee.password
          );*/
        await db.collection("employees").doc(props.employee.uid).update({
          name: name.value,
          phone: phone.value,
          address: addr.value,
          city: city.value,
          district: dist.value,
          neighborhood: nbhd.value,
        });

        var getUserByEmail = functions.httpsCallable("getUserByEmail");
        var user = (await getUserByEmail({ email: props.employee.email })).data;
        console.log(user);
        if (email.value != props.employee.email) {
          var updateEmail = functions.httpsCallable("updateEmail");
          updateEmail({
            email: email.value,
            uid: props.employee.uid,
          });
        }

        if (pwd.value.length != 0) {
          var updatePassword = functions.httpsCallable("updatePassword");
          updatePassword({
            password: pwd.value,
            uid: props.employee.uid,
          });
        }

        emit("closePopUp");
      } catch (error) {
        console.log(error.message);
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
      error,
      edit,
    };
  },
};
</script>

<style></style>
